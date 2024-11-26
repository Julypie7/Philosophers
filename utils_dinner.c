/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:14:30 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/26 15:34:41 by ineimatu         ###   ########.fr       */
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
	if (dead_check(data))
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

long	ft_get_moment_time(t_philo *philo)
{
	return (get_right_time() - philo->data->start_simul);
}

long	get_right_time(void)
{
	struct timeval	tv;
	unsigned int		current_time;

	gettimeofday(&tv, NULL);
	current_time = (unsigned int)(tv.tv_sec * 1000) + (tv.tv_usec * 0.001);
	return (current_time);
}

int my_usleep(t_philo *philo, long sleep)
{
	long time;

	time = get_right_time();
	while (dead_check(philo->data) && ((get_right_time() - time) < sleep))
		usleep(500);
	return(0);
}

/*
int my_usleep(t_philo *philo, long sleep)
{
	long	time;

	time = ft_get_moment_time(philo);
	if (!dead_check(philo->data))
		return (1);
	while (dead_check(philo->data) && ((ft_get_moment_time(philo) - time) < sleep))
		usleep(1000);
	printf("philo id = %d",philo->id);
	return (0);
}*/
