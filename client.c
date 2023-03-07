/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:13 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/07 13:14:50 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_communicate(int pid, char c)
{
	int current_bit;

	current_bit = 0;
	while (current_bit < 8)
	{
		if ((c & (1 << current_bit)) != 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(90);
		current_bit++;
	}
}

int main(int ac, char **av)
{
	(void) av;
	char *err_message;

	err_message = "invalid amount of arguments, 3 needed\n";
	if (ac == 3)
	{
		if (av[1])
			ft_communicate(av[1]);
	}
	else
		ft_putstr_fd(err_message, 1);
}
