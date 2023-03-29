/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:21 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/29 12:54:10 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	if (g_info.cpid != client->si_pid && client->si_pid != 0)
		ft_cleanserver(&binairy, &received);
	if (!g_info.cpid)
		g_info.cpid = client->si_pid;
	if (signb == SIGUSR1)
		received |= (1 << binairy);
	if (++binairy == 8)
	{	
		if (!received)
		{
			ft_putendl_fd(g_info.message, 1);
			kill(g_info.cpid, SIGUSR1);
			ft_cleanserver(&binairy, &received);
			return ;
		}
		else
			g_info.message = ft_constructstr(g_info.message, received);
		binairy = 0;
		received = 0;
	}
	kill(g_info.cpid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	act.sa_sigaction = &ft_receiver;
	act.sa_flags = SA_SIGINFO;
	g_info.message = NULL;
	g_info.cpid = 0;
	(void) av;
	if (ac != 1)
		ft_putstr_fd("no need of any input, try again\n", 1);
	else
	{
		g_info.message = ft_calloc(g_info.size + 1, sizeof(char));
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		while (3)
			pause();
	}
}
