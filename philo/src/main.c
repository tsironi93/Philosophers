/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/08 09:42:33 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_thinking(t_philo *philo, t_data *data)
{
	u_int64_t	current_time;

	current_time = get_time() - data->starting_time;
	pthread_mutex_lock(&philo->mutex);
	while (philo->time_to_eat_again > current_time)
	{
		pthread_mutex_lock(&data->print_mutex);
		current_time = get_time() - data->starting_time;
		printf(MAGENTA "%llu %d is sleeping\n" RESET, current_time,
			philo->id);
		usleep(philo->time_to_eat_again - current_time - 50);
	}
	pthread_mutex_unlock(&philo->mutex);
}

void	start_sleeping(t_philo *philo, t_data *data)
{
	p(data, CYAN, "is sleeping", philo->id);
	usleep(data->time_to_sleep * 1000);
}

void	start_eating(t_philo *philo, t_data *data)
{
	u_int64_t	current_time;

	p(data, YELLOW, "is eating", philo->id);
	usleep(data->time_to_eat * 1000);
	current_time = get_time() - data->starting_time;
	philo->time_to_eat_again = current_time + data->time_to_die;
	pthread_mutex_unlock(philo->left_fork);
	p(data, OLIVE, "left fork is down", philo->id);
	pthread_mutex_unlock(philo->right_fork);
	p(data, OLIVE, "right fork is down", philo->id);
}

void	get_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		p(data, OLIVE, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->left_fork);
		p(data, OLIVE, "has taken a fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		p(data, OLIVE, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->right_fork);
		p(data, OLIVE, "has taken a fork", philo->id);
	}
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->sim_stop)
	{
		//if (philo->philo_ate)
			//start_thinking(philo, data);
		if (!philo->philo_ate)
		{
			get_forks(philo, data);
			if (data->sim_stop)
				break ;
			start_eating(philo, data);
			if (data->sim_stop)
				break ;
			start_sleeping(philo, data);
		}
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
	//while (!data.sim_stop)
	//	monitor(&data, data.philos);
	if (!destroy_threads(&data))
		return (-1);
	return (0);
}
