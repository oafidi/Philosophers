/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:41:43 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/20 08:55:26 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_dead_flag(t_dinning *dinner)
{
	int	dead;

	pthread_mutex_lock(&dinner->dead);
	dead = dinner->is_dead;
	pthread_mutex_unlock(&dinner->dead);
	return (dead);
}

void	set_dead_flag(t_dinning *dinner, int value)
{
	pthread_mutex_lock(&dinner->dead);
	dinner->is_dead = value;
	pthread_mutex_unlock(&dinner->dead);
}

static int	have_eating(t_dinning *dinner)
{
	int	i;
	int	count;
	int	meals_eaten;

	count = 0;
	i = 0;
	while (i < dinner->nbr_philos)
	{
		pthread_mutex_lock(&dinner->meals);
		meals_eaten = dinner->philos[i].meals_eaten;
		pthread_mutex_unlock(&dinner->meals);
		if (dinner->nbr_meals <= meals_eaten)
			count++;
		i++;
	}
	return (count == dinner->nbr_philos);// wach ga3 lphilos klaw lkamiya lmatlouba
}

void	*supervisor(void *arg)
{
	int				i;
	long			last_time;
	t_philosopher	*philo;
	t_dinning		*dinner;

	dinner = (t_dinning *)arg;
	while (1)
	{
		if (dinner->nbr_meals && have_eating(dinner))//ila dekhel lst argument kanchouf wach kolchi kla fhad l7ala tawa7ed makaymout , simulation stop
			return (set_dead_flag(dinner, 1), NULL);// ga3 philos ghay7ebsso
		i = 0;
		while (i < dinner->nbr_philos)
		{
			philo = &dinner->philos[i];
			pthread_mutex_lock(&dinner->meals);
			last_time = philo->last_meal; //kan9ra akher merra kla kol phil
			pthread_mutex_unlock(&dinner->meals);
			if (get_time() - last_time > dinner->time2die) // kan9aren bli wach mafatouch lwe9t
				return (print("died", i + 1, dinner), NULL);
			i++;
		}
		usleep(500);
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->dinner->nbr_philos == 1) // ila kan philo wa7ed ghayhz fork dyalo w ghayb9a yetssena 7ta ymout
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 1) // bach manti7ch fmochkil dyal kol wa7ed yhez fork dyalo w yb9a yetssena tanya , sebe9t li 3endhom id impair
		eat_action(philo);// homa li ghayaklo lowlin, w chi lakhor ghayn3es
	while (!get_dead_flag(philo->dinner)) // ma7ed mazal tawa7ed mamat diro had routine
	{
		sleep_action(philo);
		think_action(philo);
		eat_action(philo);
	}
	return (NULL);
}
