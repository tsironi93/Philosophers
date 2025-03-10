/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:36 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/11 00:48:22 by turmoil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	uwait(uint32_t wait)
{
	uint64_t	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < wait)
		usleep(500);
}

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

bool	my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
	{
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

void	fork_assign(t_data *data, t_philo *philo, char *fork, bool set)
{
	if (my_strcmp(fork, "right"))
	{
		if (set)
			while (data->forks_table[philo->id] == true  && !sim(data))
				uwait(1);
		pthread_mutex_lock(philo->right_fork);
		data->forks_table[philo->id] = set;
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		if (set)
			while (data->forks_table[(philo->id + 1) % data->number_of_philosophers] == true  && !sim(data))
				uwait(1);
		pthread_mutex_lock(philo->left_fork);
		data->forks_table[(philo->id + 1) % data->number_of_philosophers] = set;
		pthread_mutex_unlock(philo->left_fork);
	}
}

bool	sim(t_data *data)
{
	bool	res;

	pthread_mutex_lock(&data->monitor);
	res = data->sim_stop;
	pthread_mutex_unlock(&data->monitor);
	return (res);
}

void	p(t_data *data, char *color, char *msg, int id)
{
	uint64_t	current_time;

	pthread_mutex_lock(&data->print_mutex);
	current_time = get_time() - data->starting_time;
	printf("%s%" PRIu64 " %d %s" RESET "\n", color, current_time, id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
