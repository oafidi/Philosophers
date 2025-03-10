/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:37 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/10 02:37:22 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct	s_philosopher
{
	int			id;
	pthread_t	tid;
	long		start_time;
	long		last_meal;
	int			meals_eaten;
}	t_philosopher;

typedef struct	s_dinning
{
	int				nbr_philos;
	t_philosopher	philos[200];
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	pthread_mutex_t	forks[200];
}	t_dinning;

long	ft_atol(char *str);
int		init_mutex(t_dinning *dinner);
void	destroy_mutex(t_dinning *dinner, int nbr);
void	_usleep(long useconds);
long	get_time(void);

#endif
