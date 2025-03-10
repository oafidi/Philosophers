/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:00:18 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/10 02:16:59 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_mutex(t_dinning *dinner, int nbr)
{
	int	i;

	i = 0;
	if (nbr == -1)
	{
		while (i < dinner->nbr_philos)
			pthread_mutex_destroy(&dinner->forks[i++]);
		return ;
	}
	write(2, "Failed to initialize a mutex !!\n", 33);
	while (i < nbr)
		pthread_mutex_destroy(&dinner->forks[i++]);
}

int	init_mutex(t_dinning *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nbr_philos)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL))
			return (destroy_mutex(dinner, i), 0);
		i++;
	}
	return (1);
}
