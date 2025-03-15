/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:37 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/15 06:27:09 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define	FORK 1
# define	DEAD 8
# define	MEAL 4
# define	PRINT 2

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
	int				is_dead;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	long			start_time;
	t_philosopher	philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	meals;
	pthread_mutex_t	dead;
}	t_dinning;

int		init_mutex(t_dinning *dinner);
long	get_time(void);
void	print(char *str, int philo_id, t_dinning *dinner);
void	destroy_mutex(t_dinning *dinner, int flag, int nbr);
int		check_arguments(int argc, char **argv, t_dinning *dinner);
int		init_dinner(t_dinning *dinner);
void	*routine(void *arg);
void	supervisor(t_dinning *dinner);
void	sleep_action(t_philosopher	*philo);
void	eat_action(t_philosopher	*philo);
void	think_action(t_philosopher	*philo);
void	precise_usleep(long msec, t_dinning *dinner);
int		get_dead_flag(t_dinning *dinner);

#endif
