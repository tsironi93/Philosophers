/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:48:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/01 15:34:04 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_args(char **av)
{
	char	*arg;

	av++;
	while (*av)
	{
		arg = *av;
		if (ft_atoi(arg) < 0)
			return (printf("Negative number found\n"), false);
		while (*arg)
		{
			if (*arg > '9' || *arg < '0')
				return (printf("Other character than numbers\n"), false);
			arg++;
		}
		av++;
	}
	return (true);
}
