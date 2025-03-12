/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:36 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/12 12:44:04 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_assign(t_data *data, t_philo *philo, char *fork, bool set)
{
	if (my_strcmp(fork, "right"))
	{
		if (set)
			while (data->forks_table[read_time(data, philo->id)] == true
				&& !sim(data))
				uwait(2);
		pthread_mutex_lock(philo->right_fork);
		data->forks_table[read_time(data, philo->id)] = set;
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		if (set)
			while (data->forks_table[(read_time(data, philo->id) + 1)
					% read_time(data, data->number_of_philosophers)] == true
				&& !sim(data))
				uwait(2);
		pthread_mutex_lock(philo->left_fork);
		data->forks_table[(read_time(data, philo->id) + 1)
			% data->number_of_philosophers] = set;
		pthread_mutex_unlock(philo->left_fork);
	}
}

uint16_t	read_time(t_data *data, uint16_t value)
{
	uint16_t	res;

	pthread_mutex_lock(&data->monitor);
	res = value;
	pthread_mutex_unlock(&data->monitor);
	return (res);
}

bool	sim(t_data *data)
{
	bool	res;

	pthread_mutex_lock(&data->monitor);
	res = data->sim_stop;
	pthread_mutex_unlock(&data->monitor);
	return (res);
}

void	p(t_data *data, char *color, char *msg, int id)
{
	uint64_t	current_time;

	pthread_mutex_lock(&data->print_mutex);
	current_time = get_time() - data->starting_time;
	printf("%s%" PRIu64 " %d %s" RESET "\n", color, current_time, id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}
