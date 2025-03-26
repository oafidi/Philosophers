/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:37 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/23 11:46:00 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define FORK 1
# define DEAD 8
# define MEAL 4
# define PRINT 2

typedef struct s_philosopher//had struct 3la wod kol philosopher
{
	int					id;// kaybda men 1-->nbr_philo
	pthread_t			tid;// Thread id kate3tih lek pthread_creat
	long				last_meal;// akhir merra kla fiha
	int					meals_eaten;// 3adad lwajabat li kla ghan7tajo ila dakhel last brgument
	int					l_fork;// indice dyal fork dyalo ftableau dyal mutex fork
	int					r_fork;// fork dyal li 7dah 7itach ghaykhessouh jouj bach yakol
	struct s_dinning	*dinner;// struct lkbira
}	t_philosopher;

typedef struct s_dinning
{
	int				nbr_philos;
	int				is_dead;// had flag kaybedel fih supervisor(thread li 7adya wach chi wa7ed mat wla mazal) , philos kay9raw had flag ma7edo mazal matbedelch ya3ni mazal tawa7ed mamat ya3ni ghayb9aw 3aychin
	long			time2die;
	long			time2eat;
	long			time2sleep;
	int				nbr_meals;
	long			start_time;// m3ach bda le3cha
	pthread_t		supervisor;// thread dyal supervisor
	t_philosopher	philos[200];// hna dert tableau fix 7itach lmax li y9eder lmosa7i7 yjereb bih howa 200
	pthread_mutex_t	forks[200];// 3adad forks howa 3adad lfalasifa
	pthread_mutex_t	print;// hada mutex bacch ne7mi stdin men datarace(lketba ghatkherbe9 kolchi ghaykteb)
	pthread_mutex_t	meals;// hada bach ne7mi last_meal , meals eatn 7itach philos kaybedloha  w supervisor kay9raha
	pthread_mutex_t	dead;// hada bach ne7mi dak is_dead 7itach supervisor kaybedlo, philos kay9rawh
}	t_dinning;

int		init_mutex(t_dinning *dinner);
long	get_time(void);
void	print(char *str, int philo_id, t_dinning *dinner);
void	destroy_mutex(t_dinning *dinner, int flag, int nbr);
int		check_arguments(int argc, char **argv, t_dinning *dinner);
int		init_dinner(t_dinning *dinner);
void	*routine(void *arg);
void	*supervisor(void *arg);
void	one_philo(t_philosopher *philo);
void	sleep_action(t_philosopher	*philo);
void	eat_action(t_philosopher	*philo);
void	think_action(t_philosopher	*philo);
void	precise_usleep(long msec, t_dinning *dinner);
int		get_dead_flag(t_dinning *dinner);
void	set_dead_flag(t_dinning *dinner, int value);

#endif
