/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:55:36 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/23 11:08:00 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int					id;
	pid_t				pid;
	long				last_meal;
	int					meals_eaten;
	int					flag;
	struct s_dinning	*dinner;
}	t_philosopher;

typedef struct s_dinning
{
	int				nbr_philos;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	long			start_time;
	t_philosopher	philos[200];
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meals;
	sem_t			*stop;
}	t_dinning;

int		check_arguments(int argc, char **argv, t_dinning *dinner);
void	precise_usleep(long msec);
long	get_time(void);
int		init_semaphores(t_dinning *dinner);
void	kill_processes(t_dinning *dinner, int count);
void	destroy_semaphores(t_dinning *dinner);
void	routine(t_philosopher *philo);
void	print(char *str, int philo_id, t_dinning *dinner);
void	sleep_action(t_philosopher	*philo);
void	eat_action(t_philosopher	*philo);
void	think_action(t_philosopher	*philo);
int		create_philosophers(t_dinning *dinner);
int		init_dinner(t_dinning *dinner);

#endif