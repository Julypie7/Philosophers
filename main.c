/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:14 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/26 17:16:10 by ineimatu         ###   ########.fr       */
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
	int i;
	int flag;

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
			if (ft_get_moment_time(data->philos) - data->philos[i].last_meal_time >= data->time_to_die && data->philos[i].meals_count != data->nbr_limit_meals)
				printing(data, i, DIE, ACT_DIE);
			pthread_mutex_unlock(&data->philos[i].control);
		}
	}
	to_clean(data, num_p);
}

void	print_struct(t_data *data)
{
	int i;

	i = 0;
	printf("philo num = %ld, time_to_die = %ld,time_to_eat = %ld,time_to_sleep = %ld,nbr_limit_meals = %ld, start_simul = %ld, end_simul = %d", data->philo_num, data->time_to_die, data->time_to_eat,data->time_to_sleep, data->nbr_limit_meals, data->start_simul, data->end_simul);

	while (i < data->philo_num)
	{
		printf("id = %d, meals_count = %ld, full = %d, last_meal_time = %ld", data->philos[i].id, data->philos[i].meals_count, data->philos[i].full, data->philos[i].last_meal_time);
		i++;
	}
}


int main(int ac, char **av)
{
	t_data	*data;
	int num_p;

	num_p = 0;
	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data) * 1);
		if (!data)
			return (err_msg("Malloc of data\n", 2));
		//1) errors
		if (parse_input(data, av, ac) == 1)
			return (err_msg("Invalid arguments", 2));
		//2) creating the data
		if (init_simul(data) == 1)
			return (err_msg("Allocation failed", 2));
		//print_struct(data);
		//3)
		printf("data pointer: %p\n", data); 	
		num_p = dinner_start(data);
		//print_struct(data);
		check_philo(data, num_p);
		free(data);
		//4) cleaning leaks
		return (0);		 
	}
	else
		return (err_msg("Invalid number of arguments", 2));
}
