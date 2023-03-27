/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brheaume <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:08:24 by brheaume          #+#    #+#             */
/*   Updated: 2023/03/27 12:44:07 by brheaume         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>

typedef struct s_servinfo
{
	char	*message;
	int		cpid;
}				t_servinfo;

typedef struct s_clinfo
{
	char	*message;
	int		i;
	int		current_bit;
	int		spid;
	int		length;
}			t_clinfo;

#endif
