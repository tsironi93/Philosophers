/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/04 20:06:43 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

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

void	get_forks(t_philo *philo, t_data *data)
{
	uint64_t	current_time;

	current_time = get_time();
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%llu %d has taken a fork\n", current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%llu %d has taken a fork\n", current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%llu %d is eating\n", current_time - data->starting_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*lets_play(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (!philo->id % 2)
		get_forks(philo, data);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!(init_data(ac, av, &data) || init_philos(&data)))
		return (-1);
	if (!create_threads(&data))
		return (-1);
	//if (!destroy_threads(&data))
	//		return (-1);
	return (0);
}
