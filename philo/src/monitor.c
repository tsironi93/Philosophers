/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/07 21:21:27 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_for_dead(t_data *data, t_philo *philo)
{
	int			i;
	uint64_t	current_time;

	i = -1;
	pthread_mutex_lock(&data->monitor);
	while (++i < data->number_of_philosophers)
	{
		printf("philo %d will die at %llu\n", philo[i].id, philo[i].time_to_eat_again);
		current_time = get_time() - data->starting_time;
		if (current_time > philo[i].time_to_eat_again)
		{
			pthread_mutex_lock(&philo[i].mutex);
			data->sim_stop = true;
			pthread_mutex_lock(&data->print_mutex);
			printf(RED "%llu %d died\n" RESET, current_time,
				philo[i].id);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->monitor);
	return (true);
}

bool	monitor(t_data *data, t_philo *philo)
{
	pthread_mutex_init(&data->monitor, NULL);
	while (!data->sim_stop)
	{
		if (!check_for_dead(data, philo))
			return (false);
		usleep(500000);
	}
	return (true);
}
