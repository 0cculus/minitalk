/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:13 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/29 12:53:19 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_clinfo	g_info;

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
	{
		ft_putendl_fd("message reception complete", 1);
		exit(EXIT_SUCCESS);
	}
	else if (signb == SIGUSR2)
	{
		if (g_info.length >= 0
			&& (g_info.message[g_info.i] & (1 << g_info.current_bit)))
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
	if (ac == 3)
	{
		act.sa_sigaction = &ft_sender;
		act.sa_flags = SA_SIGINFO;
		ft_init(av);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		kill(getpid(), SIGUSR2);
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
		while (3)
			pause();
	}
	else
		ft_putstr_fd(err_message, 1);
}
