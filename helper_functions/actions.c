/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:39 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/15 06:33:21 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	sleep_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep, philo->dinner);
	}
}

void	eat_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		print("is eating", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->meals);
		philo->meals_eaten++;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->dinner->meals);
		precise_usleep(philo->dinner->time2eat, philo->dinner);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
	}
}
void	think_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
		print("is thinking", philo->id, philo->dinner);
}
