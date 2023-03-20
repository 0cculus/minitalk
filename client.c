/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:13 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/14 13:45:34 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_communicate(int pid, char c)
{
	int	current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if (c & (1 << current_bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(120);
		current_bit++;
	}
}

static void	ft_gather_comm(int pid, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		ft_communicate(pid, src[i]);
	ft_communicate(pid, 0);
}

int	main(int ac, char **av)
{
	char	*err_message;

	err_message = "invalid amount of arguments, 3 needed\n";
	if (ac == 3)
	{
		if (ft_isstrdigit(av[1]))
			ft_gather_comm(ft_atoi(av[1]), av[2]);
		else
			ft_gather_comm(ft_atoi(av[2]), av[1]);
	}
	else
		ft_putstr_fd(err_message, 1);
}
