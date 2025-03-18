/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: turmoil <jtsiros93@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:57:23 by turmoil           #+#    #+#             */
/*   Updated: 2025/03/18 17:50:45 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	_start_thinking(t_philo *philo, t_data *data)
{
	p(data, MAGENTA, "is thinking", philo->id);
	if (data->number_of_philosophers % 2 == 1)
		uwait(5);
}

static void	_start_sleeping(t_philo *philo, t_data *data)
{
	p(data, CYAN, "is sleeping", philo->id);
	uwait(read_time(data, data->time_to_sleep));
}

static void	_start_eating(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time() - data->starting_time;
	pthread_mutex_lock(&data->monitor);
	philo->time_to_eat_again = current_time + data->time_to_die;
	philo->meals_ate++;
	pthread_mutex_unlock(&data->monitor);
	p(data, YELLOW, "is eating", philo->id);
	uwait(read_time(data, data->time_to_eat));
	if (philo->id % 2 == 0)
	{
		fork_assign(data, philo, "left", false);
		fork_assign(data, philo, "right", false);
	}
	else
	{
		fork_assign(data, philo, "right", false);
		fork_assign(data, philo, "left", false);
	}
}

static void	_get_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		fork_assign(data, philo, "right", true);
		if (!sim(data))
			p(data, OLIVE, "has taken a fork", philo->id);
		fork_assign(data, philo, "left", true);
		if (!sim(data))
			p(data, OLIVE, "has taken a fork", philo->id);
	}
	else
	{
		fork_assign(data, philo, "left", true);
		if (!sim(data))
			p(data, OLIVE, "has taken a fork", philo->id);
		fork_assign(data, philo, "right", true);
		if (!sim(data))
			p(data, OLIVE, "has taken a fork", philo->id);
	}
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
	{
		_start_thinking(philo, data);
		uwait(data->time_to_eat / 2);
	}
	while (!sim(data))
	{
		_get_forks(philo, data);
		if (sim(data))
			break ;
		_start_eating(philo, data);
		if (sim(data))
			break ;
		_start_sleeping(philo, data);
		if (sim(data))
			break ;
		_start_thinking(philo, data);
	}
	return (NULL);
}
