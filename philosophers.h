/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:37 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/12 06:32:28 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define FORK_M 1
# define PRINT_M 2
# define AUTHER_M 4

typedef struct	s_philosopher
{
	int			id;
	pthread_t	tid;
	long		last_meal;
	int			meals_eaten;
	int			l_fork;
	int			r_fork;
	struct s_dinning	*dinner;
}	t_philosopher;

typedef struct	s_dinning
{
	int				nbr_philos;
	t_philosopher	philos[200];
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	long			start_time;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
}	t_dinning;

long	ft_atol(char *str);
int		init_mutex(t_dinning *dinner);
long	get_time(void);
void	precise_usleep(long msec);
void	print(char *str, int philo_id, t_dinning *dinner);
void	destroy_mutex(t_dinning *dinner, int flag, int nbr);

#endif
