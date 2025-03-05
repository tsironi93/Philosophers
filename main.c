/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/05 16:44:05 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>
#include <unistd.h>

/*void	*lock_in(void *arg)
{
	int				i;
	int				j;
	struct s_data *data;

	data = (t_data *)arg;
	j = 0;
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philos[i].mutex);
		if (i == j)
		{
			pthread_mutex_unlock(&data->philos[i].mutex);

		}
	}
}*/

void	start_thinking(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->mutex);
	while (philo->time_to_eat_again > current_time)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf(MAGENTA "%llu %d is sleeping\n" RESET, current_time - data->starting_time,
			philo->id);
		usleep(philo->time_to_eat_again - current_time - 50);
	}
	pthread_mutex_unlock(&philo->mutex);
}

void	start_sleeping(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->mutex);
	usleep(data->time_to_sleep * 1000);
	pthread_mutex_lock(&data->print_mutex);
	printf(CYAN "%llu %d is sleeping\n" RESET, current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&philo->mutex);
}

void	start_eating(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->print_mutex);
	printf(YELLOW "%llu %d is eating\n" RESET, current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->time_to_eat_again += data->time_to_die;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	get_forks(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time();
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&data->print_mutex);
	printf(OLIVE "%llu %d has taken a fork\n" RESET, current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf(OLIVE "%llu %d has taken a fork\n" RESET, current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->sim_stop)
	{
		if (philo->philo_ate)
			start_thinking(philo, data);
		if (data->sim_stop)
			break ;
		if (!philo->philo_ate)
		{
			get_forks(philo, data);
			start_eating(philo, data);
		}
		if (data->sim_stop)
			break ;
		start_sleeping(philo, data);
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
	while (!data.sim_stop)
		monitor(&data, data.philos);
	if (!destroy_threads(&data))
		return (-1);
	return (0);
}
