/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:46:11 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/28 14:04:32 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	err_msg(char *str, int ex_num, t_data *data)
{
	printf(RED"%s\n"RESET, str);
	if (ex_num == 2)
		free(data);
	return (ex_num);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while (is_digit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}
