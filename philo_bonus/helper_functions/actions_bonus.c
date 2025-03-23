/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:49:08 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/23 09:18:24 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	sleep_action(t_philosopher	*philo)
{
	print("is sleeping", philo->id, philo->dinner);
	precise_usleep(philo->dinner->time2sleep);
}

void	eat_action(t_philosopher	*philo)
{
	sem_wait(philo->dinner->forks);
	print("has taken a fork", philo->id, philo->dinner);
	sem_wait(philo->dinner->forks);
	print("has taken a fork", philo->id, philo->dinner);
	print("is eating", philo->id, philo->dinner);
	sem_wait(philo->dinner->meals);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	sem_post(philo->dinner->meals);
	precise_usleep(philo->dinner->time2eat);
	sem_post(philo->dinner->forks);
	sem_post(philo->dinner->forks);
}

void	think_action(t_philosopher	*philo)
{
	print("is thinking", philo->id, philo->dinner);
}
