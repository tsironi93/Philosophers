/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:36 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/10 17:47:51 by itsiros          ###   ########.fr       */
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

void	fork_availability(t_data *data, t_philo *philo, bool fork, bool avail)
{
	pthread_mutex_lock(&data->monitor);
	if (fork)
		data->is_fork_available[(philo->id + 1)
			% data->number_of_philosophers] = avail;
	else
		data->is_fork_available[philo->id] = avail;
	pthread_mutex_unlock(&data->monitor);
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
