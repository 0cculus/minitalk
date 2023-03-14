/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:21 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/14 13:37:31 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

char	*g_message;

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
	return (res);
}

/*static char	*ft_constructstr(char *str, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = malloc(len + 2 * sizeof(char));
	ft_memmove(new, str, len);
	new[len] = c;
	new[len] = '\0';
	ft_xfree(str);
	return (new);
}*/

static void	ft_receiver(int signb, siginfo_t *info, void *unused)
{
	static int	binairy;
	static int	received;

	(void) unused;
	(void) info;
	if (signb == SIGUSR1)
		received |= (0x01 << binairy);
	binairy++;
	if (binairy == 8)
	{
		g_message = ft_constructstr(g_message, received);
		if (received == 0)
		{
			ft_putendl_fd(g_message, 1);
			g_message = ft_xfree(g_message);
			//kill(info->si_pid, SIGUSR1);
		}
		binairy = 0;
		received = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	act.sa_sigaction = &ft_receiver;
	act.sa_flags = SA_SIGINFO;
	g_message = NULL;
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
			;
	}
}
