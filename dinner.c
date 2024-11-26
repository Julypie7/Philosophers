/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:49 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/26 17:40:09 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	dinner_start(t_data *data)
{
	int	i;
	int	fin;

	i = -1;
	fin = data->philo_num;
	pthread_mutex_lock(&data->routine);
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].philo, NULL, ft_dinner, \
					&data->philos[i]))
		{
			fin = i;
			data->end_simul = 1;
			break ;
		}
		printf("we create thread\n");
	}
	data->start_simul = get_right_time();
	pthread_mutex_unlock(&data->routine);
	return (fin);
}

void	to_print(t_philo *philo, char *act)
{
	pthread_mutex_lock(&philo->data->print);
	if (dead_check(philo->data))
		printf(act, ft_get_moment_time(philo), philo->id, RESET);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_eat(t_philo *philo)
{
	if (!dead_check(philo->data))
		return ;
	pthread_mutex_lock(&philo->first_fork);
	printf("eating %d\n", philo->id);
	to_print(philo, ACT_R_FORK);
	if (&philo->first_fork != philo->second_fork)
	{
		pthread_mutex_lock(philo->second_fork);
		to_print(philo, ACT_L_FORK);
		to_print(philo, ACT_EAT);
		pthread_mutex_lock(&philo->control);
		philo->last_meal_time = ft_get_moment_time(philo);
		philo->meals_count++;
		printf("meals_count %ld\n", philo->meals_count);
		pthread_mutex_unlock(&philo->control);
		my_usleep(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(philo->second_fork);
	}
	else
		my_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork);
}

void	*ft_dinner(void *p)
{
	t_philo	*philo;

	philo = p;
	pthread_mutex_lock(&philo->data->routine);
	pthread_mutex_unlock(&philo->data->routine);
	if (philo->id % 2 != 0 && dead_check(philo->data))
		my_usleep(philo, (philo->data->time_to_eat));
	while (dead_check(philo->data) \
			&& philo->meals_count != philo->data->nbr_limit_meals)
	{
		printf("enter\n");
		philo_eat(philo);
		if (philo->meals_count != philo->data->nbr_limit_meals)
		{
			to_print(philo, ACT_SLEEP);
			my_usleep(philo, philo->data->time_to_sleep);
			to_print(philo, ACT_THINK);
		}
	}
	return (0);
}
