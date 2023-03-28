/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:13 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/28 10:09:42 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_clinfo	g_info;

/*static void	ft_communicate(int pid, char c)
{
	g_info.current_bit = 0;
	while (g_info.current_bit < 8)
	{
		if (c & (1 << g_info.current_bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(120);
		g_info.current_bit++;
	}
}

static void	ft_gather_comm(void)
{
	while (g_info.message[++g_info.i])
		ft_communicate(g_info.spid, g_info.message[g_info.i]);
	ft_communicate(g_info.spid, 0);
}*/

static void	ft_init(char **av)
{
	g_info.current_bit = 0;
	g_info.i = 0;
	if (ft_isstrdigit(av[1]))
	{
		g_info.message = av[2];
		g_info.spid = ft_atoi(av[1]);
	}
	else
	{
		g_info.message = av[1];
		g_info.spid = ft_atoi(av[2]);
	}
	g_info.length = ft_strlen(g_info.message);
}

static void	ft_sender(int signb, siginfo_t *server, void *unused)
{
	(void) unused;
	(void) server;
	if (signb == SIGUSR1)
		exit(EXIT_SUCCESS);
	else if (signb == SIGUSR2)
	{
		if (g_info.length >= 0
			&& (g_info.message[g_info.i] & (0x01 << g_info.current_bit)))
			kill(g_info.spid, SIGUSR1);
		else
			kill(g_info.spid, SIGUSR2);
		g_info.current_bit++;
		if (g_info.current_bit == 8)
		{
			g_info.i++;
			g_info.current_bit = 0;
			g_info.length--;
		}
	}
	else if (signb == -1)
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	struct sigaction	act;
	char				*err_message;

	err_message = "invalid amount of arguments, 3 needed\n";
	act.sa_sigaction = &ft_sender;
	act.sa_flags = SA_SIGINFO;
	ft_init(av);
	if (ac == 3)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		kill(getpid(), SIGUSR2);
		while (3)
			pause();
	}
	else
		ft_putstr_fd(err_message, 1);
}
