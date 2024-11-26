/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:12:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/11/26 17:56:45 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> //threads
# include <stdio.h> // printf
# include <unistd.h> // write
# include <stdlib.h> //malloc, free
# include <limits.h>
# include <sys/time.h> // gettimeofday

//colors

# define BLUE "\x1B[34m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"
# define CYAN "\x1B[36m"
# define MAGENTA "\x1B[35m"
# define YELLOW "\x1B[33m"
# define RED "\x1B[31m"
# define WHITE "\x1b[37m"

# define ACT_L_FORK "\x1B[36m[%u] %lld took left fork%s\n"
# define ACT_R_FORK "\x1B[36m[%u] %lld took right fork%s\n"
# define ACT_EAT "\x1B[32m[%u] %lld is eating%s\n"
# define ACT_SLEEP "\x1B[34m[%u] %lld is sleeping%s\n"
# define ACT_THINK "\x1B[37m[%u] %lld is thinking%s\n"
# define ACT_DIE "\x1B[31m[%u] %lld has died%s\n"

typedef pthread_mutex_t	t_mtx;

# define MAX_PHILOS 200

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_count;
	int				full;
	long			last_meal_time; // time passed from last meal
	t_mtx			first_fork;
	t_mtx			*second_fork;
	t_mtx			control;
	pthread_t		philo; // a philo is a thread
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_mtx	print;
	t_mtx	routine;
	t_mtx	check_dead;
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simul;
	int		end_simul;
	t_philo	*philos;
}	t_data;

//main

int		main(int ac, char **av);
void	check_philo(t_data *data, int num_p);
void	to_clean(t_data *data, int num_p);

//utils

int		err_msg(char *str, int ex_num);
int		is_digit(char c);
long	ft_atol(char *str);
int		my_usleep(t_philo *philo, long sleep);
long	get_right_time(void);

//parsing

int		syntax_err(char **av, int ac);
int		limits_err(char **av);
int		init_data(t_data *data, char **av);
int		parse_input(t_data *data, char **av, int ac);
long	ft_get_moment_time(t_philo *philo);

// init struct

int		init_simul(t_data *data);
int		philo_init(t_data *data);

// utils dinner

void	ft_bzero(void *s, size_t n);
int		dead_check(t_data *data);
int		printing(t_data *data, int i, int flag, char *act);

// dinner

int		dinner_start(t_data *data);
void	to_print(t_philo *philo, char *act);
void	philo_eat(t_philo *philo);
void	*ft_dinner(void *p);

#endif
