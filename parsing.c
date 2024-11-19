/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:11:45 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/15 10:18:43 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int syntax_err(char **av, int ac)
{
	int i;
	int j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] == '+')
			j++;
		else if (av[i][0] == '-')
			return (err_msg("Only positive numbers accepted", 0));
		/*while (av[i][++j] != '\0' && av[i][++j] != ' ')
			if ((!is_digit(av[i][j])) \
			&& (av[i][j] != '+' || av[i][j] != '-'))
				return (printf("heeey"), 0);*/
		while (av[i][++j] != '\0')
			if ((av[i][j] < '0' || av[i][j] > '9') \
			&& (av[i][j] != '+' || av[i][j] != '-'))
				return ( 0);
		if ((!*av[i]) || (j == 1 && (av[i][0] == '+' || av[i][0] == '-')))
			return (0);
	}
	return (1);
}

int limits_err(char **av)
{
	int len;
	int i;

	i = 0;
	while (av && av[i])
	{
		len = 0;
		while (av[i][len])
			len++;
		if (len > 10)
			return (err_msg("The value is too long", 0));
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **av)
{
	data->philo_num = ft_atol(av[1]);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (err_msg("Alloc error", 1));
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		data->nbr_limit_meals = ft_atol(av[5]);
	else
		data->nbr_limit_meals = -1;
	data->start_simul = get_right_time();
	data->end_simul = 0;
	return (0);
}

int parse_input(t_data *data, char **av, int ac)
{
	int i;
	int num;

	i = 1;
	if (!syntax_err(av, ac))
		return (1);
	if (!limits_err(av))
		return (1);	
	while (i < ac)
	{
		num = ft_atol(av[i]);
		if (i == 1 && (num < 1 || num > MAX_PHILOS))
			return (1);
		if (i == 5 && (num < 1))
			return (1);
		if ((i >= 2 && i <= 4) && (num < 60))
			return (1);
		i++;
	}
	if (init_data(data, av))
		return (1);
	return (0);
}

long	ft_get_moment_time(t_philo *philo)
{
	return (get_right_time() - philo->data->start_simul);
}
