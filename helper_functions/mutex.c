/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:00:18 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/15 01:14:28 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_mutex(t_dinning *dinner, int flag, int nbr)
{
	int	i;

	i = 0;
	if (15 == flag)
	{
		while (i < nbr)
			pthread_mutex_destroy(&dinner->forks[i++]);
		pthread_mutex_destroy(&dinner->print);
		pthread_mutex_destroy(&dinner->meals);
		pthread_mutex_destroy(&dinner->dead);
	}
	else if (6 == flag)
	{
		pthread_mutex_destroy(&dinner->print);
		pthread_mutex_destroy(&dinner->meals);
	}
	else
		pthread_mutex_destroy(&dinner->print);
}

int	init_mutex(t_dinning *dinner)
{
	int	i;

	if (pthread_mutex_init(&dinner->print, NULL))
		return (write(2, "Failed to inisialize print mutex !!\n", 37), 0);
	if (pthread_mutex_init(&dinner->meals, NULL))
	{
		write(2, "Failed to inisialize meals mutex !!\n", 37);
		return (destroy_mutex(dinner, PRINT, 0), 0);
	}
	if (pthread_mutex_init(&dinner->dead, NULL))
	{
		write(2, "Failed to inisialize dead mutex !!\n", 36);
		return (destroy_mutex(dinner, PRINT | MEAL, 0), 0);
	}
	i = 0;
	while (i < dinner->nbr_philos)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL))
		{
			write(2, "Failed to initialize a fork mutex !!\n", 38);
			return (destroy_mutex(dinner, FORK | PRINT | MEAL | DEAD, i), 0);
		}
		i++;
	}
	return (1);
}
