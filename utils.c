/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:46:11 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/25 15:55:07 by ineimatu         ###   ########.fr       */
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
