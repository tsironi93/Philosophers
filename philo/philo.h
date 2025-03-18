/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:21:55 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/18 18:00:09 by itsiros          ###   ########.fr       */
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
# include <inttypes.h>

# define RESET   "\x1b[0m"
# define OLIVE   "\x1b[2;33m"
# define RED     "\x1b[91m"
# define BLACK   "\x1b[90m"
# define GREEN   "\x1b[92m"
# define YELLOW  "\x1b[93m"
# define BLUE    "\x1b[94m"
# define MAGENTA "\x1b[95m"
# define CYAN    "\x1b[96m"
# define WHITE   "\x1b[97m"

# define MAX_P 200

typedef struct s_philo
{
	uint8_t			id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	uint64_t		time_to_eat_again;
	uint8_t			meals_ate;
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
	bool			forks_table[MAX_P];
	pthread_mutex_t	monitor;
	pthread_mutex_t	sim;
	pthread_mutex_t	print_mutex;
	uint64_t		starting_time;
	bool			sim_stop;
}				t_data;

int			ft_atoi(const char *str);
bool		my_strcmp(const char *s1, const char *s2);

bool		valid_args(char **av);
bool		init_data(int ac, char **av, t_data *data);
bool		init_philos(struct s_data *data);
bool		create_threads(t_data *data);
void		destroy_threads(t_data *data);

uint64_t	get_time(void);
void		uwait(uint32_t wait);

void		*lets_play(void *arg);
void		fork_assign(t_data *data, t_philo *philo, char *fork, bool set);

bool		monitor(t_data *data, t_philo *philo);
void		p(t_data *data, char *color, char *msg, int id);
bool		sim(t_data *data);
uint64_t	read_time(t_data *data, uint64_t value);

#endif
