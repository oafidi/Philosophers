/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:39 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/20 08:52:50 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	sleep_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep, philo->dinner);// usleep 9ed time2sleep
	}
}

void	eat_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]); // sed 3la lfork dyalek bach ta7ed mayhezha
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);// khoud dyal li 7dak , ila mal9ahach ghayb9a yetssena 7ta yetle9ha moulaha
		print("has taken a fork", philo->id, philo->dinner);
		print("is eating", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->meals);
		philo->meals_eaten++;
		philo->last_meal = get_time();// akhir merra kla fiha
		pthread_mutex_unlock(&philo->dinner->meals);
		precise_usleep(philo->dinner->time2eat, philo->dinner);// usleep 9ed time to eat
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);// tlo9 lforks
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
}

void	think_action(t_philosopher	*philo)
{
	if (!get_dead_flag(philo->dinner))
		print("is thinking", philo->id, philo->dinner);// kteb ghir message
}
