/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/01 15:09:34 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	*timep(void *arg)
{
	uint64_t	start;
	uint64_t	end;

	start = get_time();
	printf("starting time: %llu\n", start);
	usleep(1000000);
	end = get_time();
	printf("ending time: %llu\n", end);
	printf("Execution time: %llu ms\n", end - start);
	return (NULL);
}

void	init_philo(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"), exit(EXIT_FAILURE));
	if (!valid_args(av))
		return (printf("Wrong arguments\n"), exit(EXIT_FAILURE));
}

int	main(int ac, char **av)
{
	init_philo(ac, av);
	return (0);
}
