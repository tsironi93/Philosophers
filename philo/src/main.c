/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:59 by itsiros           #+#    #+#             */
/*   Updated: 2025/03/11 00:51:12 by turmoil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!init_data(ac, av, &data))
		return (-1);
	if (!init_philos(&data))
		return (-1);
	if (!create_threads(&data))
		return (-1);
	while (!sim(&data))
		if (!monitor(&data, data.philos))
			break ;
			//return (destroy_threads(&data));
	return (0);
}
