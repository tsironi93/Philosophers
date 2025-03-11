/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:48:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/11 14:09:47 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	valid_args(char **av)
{
	char	*arg;

	av++;
	while (*av)
	{
		arg = *av;
		if (ft_atoi(arg) <= 0)
			return (printf("Negative number found or 0\n"), false);
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

bool	my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
