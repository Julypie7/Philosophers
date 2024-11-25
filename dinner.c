/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:49 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/25 16:29:13 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/philo.h"

int 	dinner_start(t_data *data)
{
	int i;
	int fin;

	i = -1;
	printf("dta: %p", data);
	fin = data->philo_num;
	pthread_mutex_lock(&data->routine);
	printf("before");
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].philo, NULL, ft_dinner, &data->philos[i]))
		{
			fin = i;
			data->end_simul = 1;
			break;
		}
		printf("we create thread\n");
	}
	printf("After creating");
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
	pthread_mutex_lock(&philo->first_fork);
	printf("eating");
	to_print(philo, ACT_FORK);
	if (&philo->first_fork != philo->second_fork)
	{
		pthread_mutex_lock(philo->second_fork);
		to_print(philo, ACT_FORK);
		pthread_mutex_lock(&philo->control);
		philo->last_meal_time = ft_get_moment_time(philo);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->control);
		to_print(philo, ACT_EAT);
		my_usleep(philo, philo->data->time_to_eat);
		pthread_mutex_unlock(philo->second_fork);
	}
	else
		usleep(philo->data->time_to_die);
		//my_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork);
}

void	*ft_dinner(void *p)
{
	t_philo	*philo;

	philo = p;
	pthread_mutex_lock(&philo->data->routine);
	pthread_mutex_unlock(&philo->data->routine);
	if (philo->id % 2 != 0 && dead_check(philo->data))
		usleep(philo->data->time_to_eat);
		//my_usleep(philo, (philo->data->time_to_eat));
	while (dead_check(philo->data) && philo->meals_count != philo->data->nbr_limit_meals)
	{
		philo_eat(philo);
		if (philo->meals_count != philo->data->nbr_limit_meals)
		{
			to_print(philo, ACT_SLEEP);
			usleep(philo->data->time_to_sleep);
			//my_usleep(philo, philo->data->time_to_sleep);
			to_print(philo, ACT_THINK);
		}
	}
	return (0);
}
