/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:21:55 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/01 17:22:22 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>

# define MAX_P 200

typedef struct s_data
{
	uint8_t		number_of_philosophers;
	uint16_t	time_to_die;
	uint16_t	time_to_eat;
	uint16_t	time_to_sleep;
	uint16_t	number_of_times_each_philosopher_must_eat;
}				t_data;

typedef struct s_philo
{
	uint8_t			id;
	struct s_data	*data;
}			t_philo;

int		ft_atoi(const char *str);
bool	valid_args(char **av);

#endif
