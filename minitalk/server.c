/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:04 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/05 21:44:21 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ipc.h"

void	signal_handler2(int *expected_bytes, char buffer[5], int *byte_index)
{
	if (*expected_bytes == 0)
	{
		if ((buffer[0] & 0x80) == 0x00)
			*expected_bytes = 1;
		else if ((buffer[0] & 0xE0) == 0xC0)
			*expected_bytes = 2;
		else if ((buffer[0] & 0xF0) == 0xE0)
			*expected_bytes = 3;
		else if ((buffer[0] & 0xF8) == 0xF0)
			*expected_bytes = 4;
		else
		{
			*expected_bytes = 0;
			*byte_index = 0;
			return ;
		}
	}
	if (*byte_index == *expected_bytes)
	{
		buffer[*expected_bytes] = '\0';
		write(STDOUT_FILENO, buffer, *expected_bytes);
		*byte_index = 0;
		*expected_bytes = 0;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit_count = 0;
	static int	byte_index = 0;
	static int	expected_bytes = 0;
	static char	buffer[5] = {0};

	(void)context;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		bit_count = 0;
		if (c == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		buffer[byte_index++] = c;
		signal_handler2(&expected_bytes, buffer, &byte_index);
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
