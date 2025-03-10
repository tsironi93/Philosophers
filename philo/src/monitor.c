/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/10 18:17:14 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

static bool	_check_for_dead(t_data *data, t_philo *philo)
{
	int			i;
	uint64_t	current_time;
	uint64_t	time_to_eat;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->monitor);
		time_to_eat = philo[i].time_to_eat_again;
		pthread_mutex_unlock(&data->monitor);
		current_time = get_time() - data->starting_time;
		if (current_time >= time_to_eat)
		{
			pthread_mutex_lock(&data->monitor);
			data->sim_stop = true;
			pthread_mutex_unlock(&data->monitor);
			p(data, RED, "died", philo->id);
			pthread_mutex_lock(&data->print_mutex);
			return (false);
		}
	}
	return (true);
}

static bool	_check_meals(t_data *data, t_philo *philo)
{
	int		i;
	uint8_t	meals;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->monitor);
		meals = philo[i].meals_ate;
		pthread_mutex_unlock(&data->monitor);
		if (data->number_of_times_each_philosopher_must_eat != meals)
			return (false);
	}
	pthread_mutex_lock(&data->monitor);
	data->sim_stop = true;
	pthread_mutex_unlock(&data->monitor);
	pthread_mutex_lock(&data->print_mutex);
	return (true);
}

bool	monitor(t_data *data, t_philo *philo)
{
	if (!_check_for_dead(data, philo))
		return (false);
	if (data->number_of_times_each_philosopher_must_eat)
	{
		if (_check_meals(data, philo))
			return (false);
	}
	usleep(42);
	return (true);
}
