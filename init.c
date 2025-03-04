/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:20:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/04 20:03:33 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

bool	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"), false);
	if (!valid_args(av))
		return (printf("Wrong arguments\n"), false);
	if (ft_atoi(av[1]) > 200)
		return (printf("Too many philosophers\n"), false);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->sleep_mutex, NULL);
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i], NULL);
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork
			= &data->forks[i + 1 % data->number_of_philosophers];
		data->philos[i].philo_ate = false;
		data->philos[i].data = data;
	}
	data->starting_time = get_time();
	return (true);
}

bool	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i].thread, NULL, lets_play,
				(void *)&data->philos[i]))
			return (printf("Error creating threads\n"), false);
	}
	return (true);
}

bool	destroy_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Error joining threads\n"), false);
	return (true);
}
