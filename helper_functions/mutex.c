/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:00:18 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/12 03:05:26 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	destroy_mutex(t_dinning *dinner, int flag, int nbr)
{
	int	i;

	i = 0;
	if (7 == flag)
	{
		while (i < nbr)
			pthread_mutex_destroy(&dinner->forks[i++]);
		pthread_mutex_destroy(&dinner->print);
	}
	else
		pthread_mutex_destroy(&dinner->print);
}

int	init_mutex(t_dinning *dinner)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&dinner->print, NULL))
		return (write(2, "Failed to inisialize print mutex !!\n", 37), 0);
	//if(Auther mutex)--> print mutex ;destroy_mutex(dinner, PRINT_M, i)
	while (i < dinner->nbr_philos)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL))
		{
			write(2, "Failed to initialize a fork mutex !!\n", 38);
			return (destroy_mutex(dinner, FORK_M | PRINT_M | AUTHER_M, i), 0);
		}
		i++;
	}
	return (1);
}