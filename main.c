/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:14 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/26 17:44:25 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	to_clean(t_data *data, int num_p)
{
	int	i;

	i = -1;
	while (++i < num_p)
		pthread_join(data->philos[i].philo, NULL);
	i = -1;
	while (++i < num_p)
	{
		pthread_mutex_destroy(&data->philos[i].control);
		pthread_mutex_destroy(&data->philos[i].first_fork);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->check_dead);
	if (data && data->philos)
		free(data->philos);
}

void	check_philo(t_data *data, int num_p)
{
	int	i;
	int	flag;

	flag = 0;
	while (dead_check(data) && flag != data->philo_num)
	{
		i = -1;
		flag = 0;
		while (++i < num_p)
		{
			pthread_mutex_lock(&data->philos[i].control);
			if (data->philos[i].meals_count == data->nbr_limit_meals)
				flag++;
			if ((ft_get_moment_time(data->philos) \
						- data->philos[i].last_meal_time) >= \
					data->time_to_die && data->philos[i].meals_count \
					!= data->nbr_limit_meals)
				printing(data, i, DIE, ACT_DIE);
			pthread_mutex_unlock(&data->philos[i].control);
		}
	}
	to_clean(data, num_p);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		num_p;

	num_p = 0;
	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data) * 1);
		if (!data)
			return (err_msg("Malloc of data\n", 2));
		if (parse_input(data, av, ac) == 1)
			return (err_msg("Invalid arguments", 2));
		if (init_simul(data) == 1)
			return (err_msg("Allocation failed", 2));
		num_p = dinner_start(data);
		check_philo(data, num_p);
		free(data);
		return (0);
	}
	else
		return (err_msg("Invalid number of arguments", 2));
}
