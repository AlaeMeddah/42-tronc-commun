/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:38 by almeddah          #+#    #+#             */
/*   Updated: 2025/02/11 11:00:32 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ipc.h"

volatile int	g_received = 0;

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("character received by the server\n", STDOUT_FILENO);
	else if (sig == SIGUSR2)
		ft_putstr_fd("message received completly by the server\n",
			STDOUT_FILENO);
	g_received = 1;
}

void	send_message(int pid, unsigned char *message)
{
	int				i;
	unsigned char	c;

	while (*message)
	{
		i = 8;
		c = *message++;
		while (i--)
		{
			if (c & (1 << i))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
		while (!g_received)
			pause();
		g_received = 0;
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	unsigned char		*message;
	struct sigaction	action;

	if (argc == 3)
	{
		pid = atoi(argv[1]);
		message = (unsigned char *)argv[2];
		action.sa_handler = signal_handler;
		action.sa_flags = 0;
		sigemptyset(&action.sa_mask);
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
		send_message(pid, message);
	}
	else
		ft_putstr_fd("Error: Wrong arguments\n", STDOUT_FILENO);
	return (0);
}
