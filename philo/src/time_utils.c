/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:11:41 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/11 14:12:03 by itsiros          ###   ########.fr       */
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
