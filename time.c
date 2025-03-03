/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:32:00 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/03 12:33:40 by itsiros          ###   ########.fr       */
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
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex);
	start = get_time();
	usleep(1000000);
	end = get_time();
	printf("Execution time: %llu ms\n", end - start);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}
