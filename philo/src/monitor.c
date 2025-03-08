/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:34:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/08 15:43:41 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_for_dead(t_data *data, t_philo *philo)
{
	int			i;
	uint64_t	current_time;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		current_time = get_time() - data->starting_time;
		if (current_time >= philo[i].time_to_eat_again)
		{
			data->sim_stop = true;
			printf(RED "%llu %d died\n" RESET, current_time, philo[i].id);
			return (false);
		}
	}
	return (true);
}

bool	monitor(t_data *data, t_philo *philo)
{
	if (!check_for_dead(data, philo))
		return (false);
	usleep(42);
	return (true);
}
