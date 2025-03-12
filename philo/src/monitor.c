/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/12 11:30:20 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	_check_for_dead(t_data *data, t_philo *philo)
{
	int			i;
	uint64_t	current_time;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		current_time = get_time() - data->starting_time;
		if (current_time >= read_time(data, philo[i].time_to_eat_again))
		{
			pthread_mutex_lock(&data->monitor);
			data->sim_stop = true;
			pthread_mutex_unlock(&data->monitor);
			p(data, RED, "died", i);
			return (false);
		}
	}
	return (true);
}

static bool	_check_meals(t_data *data, t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < data->number_of_philosophers)
		if (data->number_of_times_each_philosopher_must_eat
			!= read_time(data, philo[i].meals_ate))
			return (false);
	pthread_mutex_lock(&data->monitor);
	data->sim_stop = true;
	pthread_mutex_unlock(&data->monitor);
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
