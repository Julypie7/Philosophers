/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:46:11 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/25 12:48:52 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	err_msg(char *str, int ex_num)
{
	printf(RED"%s\n"RESET, str);
	return (ex_num);
}

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	long num;
	int i;
	
	i = 0;
	num = 0;
	while (is_digit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (num > INT_MAX)
		return (err_msg("Value is too big", -1));
	return ((int)num);
}

int my_usleep(t_philo *philo, long sleep)
{
	long	time;

	time = ft_get_moment_time(philo);
	if (dead_check(philo->data))
		return (1);
	while (!dead_check(philo->data) && ((ft_get_moment_time(philo) - time) < sleep))
		usleep(1000);
	return (0);
}

long	get_right_time(void)
{
	struct timeval	tv;
	long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
	return (current_time);
}
