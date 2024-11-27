/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:51:26 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/27 14:13:31 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].first_fork, NULL))
			return (err_msg("Error init", 1));
		if (pthread_mutex_init(&data->philos[i].control, NULL))
			return (err_msg("Error mutex init", 1));
		if (i > 0)
			data->philos[i].second_fork = &data->philos[i - 1].first_fork;
		i++;
	}
	return (0);
}

int	init_simul(t_data *data)
{
	if (philo_init(data) == 1)
		return (1);
	data->philos[0].second_fork = &data->philos[data->philo_num - 1].first_fork;
	if (pthread_mutex_init(&data->routine, NULL))
		return (err_msg("Error init!", 1));
	if (pthread_mutex_init(&data->check_dead, NULL))
		return (err_msg("Error init!", 1));
	if (pthread_mutex_init(&data->print, NULL))
		return (err_msg("Error init!", 1));
	return (0);
}
