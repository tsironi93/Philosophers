/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:20:51 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/03 16:11:29 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, struct s_data *data)
{
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"), exit(EXIT_FAILURE));
	if (!valid_args(av))
		return (printf("Wrong arguments\n"), exit(EXIT_FAILURE));
	if (ft_atoi(av[1]) > 200)
		return (printf("Too many philosophers\n"), exit(EXIT_FAILURE));
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void	init_philos(struct s_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].is_fork_available = true;
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		data->philos[i].data = data;
	}
	data->starting_time = get_time();
}

void	create_threads(struct s_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		if (pthread_create(&data->philos[i].thread, NULL, lets_play, &data->philos[i]))
			printf("Error creating threads\n");
	i = -1;
	while (++i < data->number_of_philosophers)
		if (pthread_join(data->philos[i].thread, NULL))
			printf("Error joining threads\n");
}
