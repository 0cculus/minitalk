/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:21 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/28 10:30:49 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

struct s_servinfo	g_info;

static char	*ft_constructstr(char *src, int bit)
{
	int		len_src;
	char	*res;
	char	c;
	int		i;

	i = 0;
	c = (char)bit;
	len_src = ft_strlen(src);
	res = ft_calloc(len_src + 2, sizeof(char));
	if (src)
	{
		while (src[i])
		{
			res[i] = src[i];
			i++;
		}
	}
	res[i] = c;
	ft_xfree(src);
	return (res);
}

static void	ft_cleanserver(int *binairy, int *received)
{
	ft_putendl_fd("freedom", 1);
	g_info.message = ft_xfree(g_info.message);
	g_info.cpid = 0;
	*binairy = 0;
	*received = 0;
}

static void	ft_receiver(int signb, siginfo_t *client, void *unused)
{
	static int	binairy;
	static int	received;

	(void) unused;
	if (!g_info.cpid)
		g_info.cpid = client->si_pid;
	if (client->si_pid != g_info.cpid)
		ft_cleanserver(&binairy, &received);
	if (signb == SIGUSR1)
	{
		ft_putendl_fd("SIGUSR1", 1);
		received |= (1 << binairy);
	}
	else
		ft_putendl_fd("SIGUSR2", 1);
	binairy++;
	if (binairy == 8)
	{	
		if (!received)
		{
			ft_putendl_fd(g_info.message, 1);
			g_info.message = ft_xfree(g_info.message);
			kill(client->si_pid, SIGUSR1);
		}
		else
			g_info.message = ft_constructstr(g_info.message, received);
		binairy = 0;
		received = 0;
	}
	ft_putendl_fd("sending", 1);
	kill(client->si_pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	act.sa_sigaction = &ft_receiver;
	act.sa_flags = SA_SIGINFO;
	g_info.message = NULL;
	(void) av;
	if (ac != 1)
		ft_putstr_fd("no need of any input, try again\n", 1);
	else
	{
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		while (3)
			pause();
	}
}
