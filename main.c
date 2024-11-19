/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:14 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/18 17:03:05 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

//philo 5 880 300 300 [5]

void	to_clean(t_data *data, int num_p)
{
	int	i;

	i = -1;
	while (++i < num_p)
		pthread_join(data->philos[i].philo, NULL);
	i = -1;
	while (++i < num_p)
	{
		pthread_mutex_destroy(data->philos[i].control);
		pthread_mutex_destroy(data->philos[i].first_fork);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->check_dead);
	if (data && data->philos)
		free(data->philos);	
}
void	check_philo(t_data *data, int num_p)
{
	int i;
	int flag;

	flag = 0;
	while (!dead_check(data) && flag == 0)
	{
		i = -1;
		flag = 1;
		while (++i < num_p)
		{
			pthread_mutex_lock(data->philos->control);
			if (data->philos[i].meals_count != data->nbr_limit_meals)				flag = 0;
			if (ft_get_moment_time(&data->philos[i]) - data->philos[i].last_meal_time >= data->time_to_die && data->philos[i].meals_count != data->nbr_limit_meals)
				printing(data, i, DIE, ACT_DIE);
			pthread_mutex_unlock(&data->philo->control);
		}
	}
	to_clean(data, num_p);
}

int main(int ac, char **av)
{
	t_data	data;
	int num_p;

	if (ac == 5 || ac == 6)
	{
		ft_bzero(&data, sizeof(data));
		//1) errors
		if (parse_input(&data, av, ac) == 1)
			return (err_msg("Invalid arguments", 2));
		//2) creating the data
		if (init_data(&data, av) == 1)
			return (err_msg("Allocation failed", 2));
		//3) 
		num_p = dinner_start(&data);
		check_philo(&data, num_p);
		//4) cleaning leaks
		clean(&data);*/
		return (0);		 
	}
	else
		return (err_msg("Invalid number of arguments", 2));
}
