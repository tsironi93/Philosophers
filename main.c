/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/01 17:39:55 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	*timep(void *arg)
{
	uint64_t	start;
	uint64_t	end;

	start = get_time();
	printf("starting time: %llu\n", start);
	usleep(1000000);
	end = get_time();
	printf("ending time: %llu\n", end);
	printf("Execution time: %llu ms\n", end - start);
	return (NULL);
}

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
	if (av[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
}

void	init_philos(struct s_data *data)
{
	struct s_philo	philos[MAX_P];
	int				i;

	i = 0;
	while (i <= data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		printf("Philo nmb %d has an id\n", philos[i].id);
		i++;
	}
}

int	main(int ac, char **av)
{
	struct s_data	data;

	init_data(ac, av, &data);
	init_philos(&data);
	create_philo_threads(&data); // To be done
	return (0);
}
