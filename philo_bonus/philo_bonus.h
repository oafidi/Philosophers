/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:55:36 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 14:03:44 by oafidi           ###   ########.fr       */
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

typedef struct s_philosopher
{
	int					id;
	pid_t				pid;
	long				last_meal;
	int					meals_eaten;
	struct s_dinning	*dinner;
}	t_philosopher;

typedef struct s_dinning
{
	int				nbr_philos;
	int				is_dead;
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	long			start_time;
	pthread_t		supervisor;
	t_philosopher	philos[200];
	sem_t			*forks;
	sem_t			*print;
}	t_dinning;

int		check_arguments(int argc, char **argv, t_dinning *dinner);
void	precise_usleep(long msec, t_dinning *dinner);
long	get_time(void);
int		init_semaphores(t_dinning *dinner);
void	close_semaphores(t_dinning *dinner);
void	destroy_semaphores(t_dinning *dinner);

#endif