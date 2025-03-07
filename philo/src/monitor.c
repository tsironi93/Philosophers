/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/07 10:28:05 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stdio.h>

bool	check_for_dead(t_data *data, t_philo *philo)
{
	int			i;
	uint64_t	current_time;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		current_time = get_time();
		if (current_time - data->starting_time > philo[i].time_to_eat_again)
		{
			pthread_mutex_lock(&philo[i].mutex);
			data->sim_stop = true;
			pthread_mutex_lock(&data->print_mutex);
			printf(RED "%llu %d died\n" RESET, current_time - data->starting_time,
				philo[i].id);
			break ;
		}
	}
	return (true);
}

bool	monitor(t_data *data, t_philo *philo)
{
	philo = data->philos;
	while (!data->sim_stop)
		check_for_dead(data, philo);
	return (true);
}
