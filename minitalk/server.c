/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:04 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/12 15:31:05 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ipc.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	c = 0;

	(void)context;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == 0)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			ft_putchar_fd(c, STDOUT_FILENO);
			kill(info->si_pid, SIGUSR1);
		}
		c = 0;
		bit_count = 0;
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
