/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:21:55 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:16 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

# define MAX_P 200

typedef struct s_philo
{
	uint8_t			id;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			philo_ate;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	uint8_t			number_of_philosophers;
	uint16_t		time_to_die;
	uint16_t		time_to_eat;
	uint16_t		time_to_sleep;
	uint16_t		number_of_times_each_philosopher_must_eat;
	t_philo			philos[MAX_P];
	pthread_mutex_t	forks[MAX_P];
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	print_mutex;
	uint64_t		starting_time;
}				t_data;

int			ft_atoi(const char *str);
bool		valid_args(char **av);
uint64_t	get_time(void);
bool		init_data(int ac, char **av, t_data *data);
bool		init_philos(struct s_data *data);
bool		create_threads(t_data *data);
bool		destroy_threads(t_data *data);
void		*lets_play(void *arg);
void		get_forks(t_philo *philo, t_data *data);

#endif
