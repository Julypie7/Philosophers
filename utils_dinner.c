/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:14:30 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/18 16:05:52 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	dead_check(t_data *data)
{
	int dead;

	dead = 1;
	pthread_mutex_lock(&data->check_dead);
	if (data->end_simul == 1)
		dead = 0;
	pthread_mutex_unlock(&data->check_dead);
	return (dead);
}

int	printing(t_data *data, int i, int flag, char *act)
{
	pthread_mutex_lock(&data->print);
	if (dead_check(data->philos[i]))
	{
		if (flag == DIE)
		{
			pthread_mutex_lock(&data->check_dead);
			data->end_simul = 1;
			pthread_mutex_unlock(&data->check_dead);
		}
		printf(act, ft_get_moment_time(data->philos), data->philos[i].id, RESET);
	}
	pthread_mutex_unlock(&data->print);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*string;
	size_t			i;
	unsigned char	zero;

	zero = '\0';
	string = (unsigned char *)s;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			string[i] = zero;
			i++;
		}
	}
}
