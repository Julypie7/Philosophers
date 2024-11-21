/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:51:26 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/21 15:19:31 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pthread.h"
# include "inc/philo.h"
/*
static void fork_init(t_philo philo, t_fork *forks, int philo_pos)
{
	int nbr;

	nbr = philo.data->philo_num;
	philo.second_fork = &forks[philo_pos];
	philo.second_fork = &forks[(philo_pos) % nbr];
	if (philo.id % 2)
	{
		philo.first_fork = &forks[philo_pos];
		philo.second_fork = &forks[(philo_pos) % nbr];
	}
}
*/
void philo_init(t_data *data)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < data->philo_num)
	{
		philo = data->philos;
		philo[i].id = i;
		philo[i].full = 0;
		philo[i].meals_count = 0;
		philo[i].data = data;
		if (i > 0)
			philo[i].second_fork = philo[i - 1].first_fork;
	}
	philo[0].second_fork =&philo[data->philo_num - 1].first_fork;
}

int	init_simul(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(t_fork) * data->philo_num);
	if (!data->forks)
		return(err_msg("Error malloc!", 1));
	while (++i < data->philo_num)
	{
		if (pthread_mutex_init(&data->philo[i].first_fork, NULL))
			return(err_msg("Error init", 1));
		if (pthread_mutex_init(&data->philo[i].control, NULL))
			return(err_msg("Error mutex init", 1));
	}
	philo_init(data);
	if (pthread_mutex_init(&data->routine, NULL))
		return (err_msg("Error init!", 1));
	if (pthread_mutex_init(&data->check_dead, NULL))
		return (err_msg("Error init!", 1));
	if (pthread_mutex_init(&data->print, NULL))
		return (err_msg("Error init!", 1));
	return (0);
}
