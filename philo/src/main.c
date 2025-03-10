/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/10 18:39:57 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_thinking(t_philo *philo, t_data *data)
{
	p(data, MAGENTA, "is thinking", philo->id);
	if (data->number_of_philosophers % 2 == 1)
		uwait(30);
}

void	start_sleeping(t_philo *philo, t_data *data)
{
	p(data, CYAN, "is sleeping", philo->id);
	uwait(data->time_to_sleep);
}

void	start_eating(t_philo *philo, t_data *data)
{
	u_int64_t	current_time;

	p(data, YELLOW, "is eating", philo->id);
	current_time = get_time() - data->starting_time;
	pthread_mutex_lock(&data->monitor);
	philo->meals_ate++;
	philo->time_to_eat_again = current_time + data->time_to_die;
	pthread_mutex_unlock(&data->monitor);
	uwait(data->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		fork_availability(data, philo, true, false);
		pthread_mutex_unlock(philo->right_fork);
		fork_availability(data, philo, false, false);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		fork_availability(data, philo, false, false);
		pthread_mutex_unlock(philo->left_fork);
		fork_availability(data, philo, true, false);
	}
}

void	get_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		fork_availability(data, philo, false, false);
		p(data, OLIVE, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->left_fork);
		fork_availability(data, philo, true, false);
		p(data, OLIVE, "has taken a fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		fork_availability(data, philo, true, false);
		p(data, OLIVE, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->right_fork);
		fork_availability(data, philo, false, false);
		p(data, OLIVE, "has taken a fork", philo->id);
	}
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	start_thinking(philo, data);
	if (philo->id % 2 == 1)
		uwait(data->time_to_eat / 2);
	while (!sim(data))
	{
		get_forks(philo, data);
		if (sim(data))
			break ;
		start_eating(philo, data);
		if (sim(data))
			break ;
		start_sleeping(philo, data);
		if (sim(data))
			break ;
		start_thinking(philo, data);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!init_data(ac, av, &data))
		return (-1);
	if (!init_philos(&data))
		return (-1);
	if (!create_threads(&data))
		return (-1);
	while (!sim(&data))
		if (!monitor(&data, data.philos))
			return (destroy_threads(&data));
	return (0);
}
