/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:22:02 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/22 14:22:17 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*check_death(void *arg)
{
	t_philosopher	*philo;
	long			last_time;

	philo = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philo->dinner->meals);
		last_time = philo->last_meal;
		sem_post(philo->dinner->meals);
		if (get_time() - last_time > philo->dinner->time2die)
			return (print("died", philo->id, philo->dinner), NULL);
		usleep(100);
	}
}

void	routine(t_philosopher *philo)
{
	pthread_t	supervisor;

	if (pthread_create(&supervisor, NULL, check_death, philo))
	{
		write(2, "Failed to create a supervisor thread !!\n", 41);
		return ;
	}
	pthread_detach(supervisor);
	while (1)
	{
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
}
