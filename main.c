/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/03 16:22:20 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	get_forks(t_philo *philo, t_philo *right_philo, t_data *data)
{
	uint64_t	current_time;

	if (philo->id < right_philo->id)
	{
		pthread_mutex_lock(&philo->mutex);
		pthread_mutex_lock(&right_philo->mutex);
	}
	else
	{
		pthread_mutex_lock(&right_philo->mutex);
		pthread_mutex_lock(&philo->mutex);
	}
	current_time = get_time();
	printf("%llu %d has taken a fork\n", current_time - data->starting_time,
		philo->id);
	printf("%llu %d has taken a fork\n", current_time - data->starting_time, philo->id);
	usleep(data->time_to_eat * 1000);
	printf("%llu %d is eating\n", current_time - data->starting_time, philo->id);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&right_philo->mutex);
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_philo		*right_philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	right_philo = &data->philos[(philo->id) % data->number_of_philosophers];
	get_forks(philo, right_philo, data);
	return (NULL);
}

int	main(int ac, char **av)
{
	struct s_data	data;

	init_data(ac, av, &data);
	init_philos(&data);
	create_threads(&data);
	return (0);
}
