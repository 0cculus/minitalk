/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:32:21 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/07 13:58:39 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_constructstr(char *src, char c)
{
	return (ft_strcombine(src, &c));
}

/*static void	ft_receiver(int signb, siginfo_t *info, void *unused)
{
	int received;

	(void) unused;
}*/

int	main(int ac, char **av)
{
	(void) av;
	if (ac != 1)
		ft_putstr_fd("no need of any input, try again\n", 1);
	else
	{
		ft_putnbr_fd(1, getpid());
		ft_putchar_fd(1, '\n');
		while (1)
			;
	}
}
