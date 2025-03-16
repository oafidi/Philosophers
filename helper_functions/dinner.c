/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:45 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/16 06:48:16 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_philosopher(t_dinning *dinner)
{
	int i;
	t_philosopher	*philo;

	i = 0;
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		philo->id = i + 1;
		pthread_mutex_lock(&dinner->meals);
		philo->last_meal = get_time();
		//printf("last time -->%ld\n",philo->last_meal);
		philo->meals_eaten = 0;
		pthread_mutex_unlock(&dinner->meals);
		philo->l_fork = i;
		philo->r_fork = (i + 1) % dinner->nbr_philos;
		philo->dinner = dinner;
		i++;
	}
	// i = 0;
	// while (i < dinner->nbr_philos)
	// {
	// 	printf("id --> %d\n", dinner->philos[i].id);
	// 	i++;
	// }

}

int	init_dinner(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	if (!init_mutex(dinner))
		return (0);
	dinner->start_time = get_time();
	set_dead_flag(dinner, 0);
	init_philosopher(dinner);
	if (pthread_create(&dinner->supervisor, NULL, supervisor, dinner))
		return (write(2, "Failed to create supervisor thread !!\n", 39), 0);
	while (i < dinner->nbr_philos)
	{
		philo = &(dinner->philos[i]);
		if (pthread_create(&(philo->tid), NULL, routine, philo))
			return (set_dead_flag(dinner, 1), write(2, "Failed to create a philosopher thread !!\n", 42), 0);
		i++;
	}
	if (pthread_join(dinner->supervisor, NULL))
		return (set_dead_flag(dinner, 1), write(2, "Failed to detach supervisor thread !!\n", 39), 0); // verifier !!
	i = 0;
	while (i < dinner->nbr_philos)
	{
		if (pthread_join(dinner->philos[i].tid, NULL))
			return (set_dead_flag(dinner, 1), write(2, "Failed to detach a philo thread !!\n", 36), 0); // verifier !!
		i++;
	}
	return (1);
}
