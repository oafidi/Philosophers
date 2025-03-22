/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:06:56 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 14:03:13 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_semaphores(t_dinning *dinner)
{
	sem_unlink("/print_sem");
	sem_unlink("/forks_sem");
	dinner->print = sem_open("/print_sem", O_CREAT, 0600, 1);
	if (dinner->print == SEM_FAILED)
		return (write(2, "Failed to inisialize print semaphore !!\n", 41), 0);
	dinner->forks = sem_open("/forks_sem", O_CREAT, 0600, dinner->nbr_philos);
	if (dinner->forks == SEM_FAILED)
	{
		sem_close(dinner->print);
		sem_unlink("/print_sem");
		return (write(2, "Failed to inisialize forks semaphore !!\n", 41), 0);
	}
	return (1);
}

void	close_semaphores(t_dinning *dinner)
{
	sem_close(dinner->print);
	sem_close(dinner->forks);
}

void	destroy_semaphores(t_dinning *dinner)
{
	close_semaphores(dinner);
	sem_unlink("/print_sem");
	sem_unlink("/forks_sem");
}