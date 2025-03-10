/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/09 00:21:31 by turmoil          ###   ########.fr       */
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
		if (current_time >= philo[i].time_to_eat_again)
		{
            p(data, RED, "died", philo->id);
			return (false);
		}
	}
	return (true);
}

static bool _check_meals(t_data *data, t_philo *philo)
{
    int i;

    i = -1;
    while (++i < data->number_of_philosophers)
    {
        if (data->number_of_times_each_philosopher_must_eat != philo[i].meals_ate)
            return (false);
    }
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
