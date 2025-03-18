/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:36 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/18 18:26:20 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	read_t(t_data *data, uint8_t pos)
{
	bool	a;

	pthread_mutex_lock(&data->monitor);
	a = data->forks_table[pos];
	pthread_mutex_unlock(&data->monitor);
	return (a);
}

void	write_t(t_data *data, uint8_t pos, bool set)
{
	pthread_mutex_lock(&data->monitor);
	data->forks_table[pos] = set;
	pthread_mutex_unlock(&data->monitor);
}

void	fork_assign(t_data *data, t_philo *philo, char *fork, bool set)
{
	if (my_strcmp(fork, "right"))
	{
		if (set)
			while (read_t(data, philo->id) == true && !sim(data))
				uwait(2);
		pthread_mutex_lock(philo->right_fork);
		write_t(data, philo->id, set);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		if (set)
			while (read_t(data, (philo->id + 1)
					% read_time(data, data->number_of_philosophers)) == true
				&& !sim(data))
				uwait(2);
		pthread_mutex_lock(philo->left_fork);
		write_t(data, (philo->id + 1) % data->number_of_philosophers, set);
		pthread_mutex_unlock(philo->left_fork);
	}
}

uint64_t	read_time(t_data *data, uint64_t value)
{
	uint64_t	res;

	pthread_mutex_lock(&data->monitor);
	res = value;
	pthread_mutex_unlock(&data->monitor);
	return (res);
}

bool	sim(t_data *data)
{
	bool	res;

	pthread_mutex_lock(&data->sim);
	res = data->sim_stop;
	pthread_mutex_unlock(&data->sim);
	return (res);
}
