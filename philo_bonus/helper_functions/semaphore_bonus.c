/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:06:56 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/22 13:41:17 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_semaphores(t_dinning *dinner)
{
	sem_unlink("/print_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/meals_sem");
	sem_unlink("/stop_sem");
	dinner->print = sem_open("/print_sem", O_CREAT, 0600, 1);
	dinner->forks = sem_open("/forks_sem", O_CREAT, 0600, dinner->nbr_philos);
	dinner->meals = sem_open("/meals_sem", O_CREAT, 0600, 1);
	dinner->stop = sem_open("/stop_sem", O_CREAT, 0600, 0);
	if (dinner->stop == SEM_FAILED || dinner->forks == SEM_FAILED
		|| dinner->meals == SEM_FAILED || dinner->print == SEM_FAILED)
	{
		destroy_semaphores(dinner);
		return (write(2, "Failed to inisialize semaphores !!\n", 36), 0);
	}
	return (1);
}

void	destroy_semaphores(t_dinning *dinner)
{
	sem_close(dinner->forks);
	sem_close(dinner->meals);
	sem_close(dinner->print);
	sem_close(dinner->stop);
	sem_unlink("/print_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/meals_sem");
	sem_unlink("/stop_sem");
}

void	kill_processes(t_dinning *dinner, int count)
{
	int	i;

	i = 0;
	while (i < count)
		kill(dinner->philos[i++].pid, SIGKILL);
}