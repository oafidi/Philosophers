/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:30 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/12 06:50:52 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
	{
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep);
	}
	while (get_time() - philo->dinner->start_time != philo->dinner->time2die)
	{
		pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
		print("has taken a fork", philo->id, philo->dinner);
		print("is eating", philo->id, philo->dinner);
		philo->meals_eaten++;
		precise_usleep(philo->dinner->time2eat);
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
		print("is thinking", philo->id, philo->dinner);
		print("is sleeping", philo->id, philo->dinner);
		precise_usleep(philo->dinner->time2sleep);
	}
	return (NULL);
}

static int	init_dinner(t_dinning *dinner)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	dinner->start_time = get_time();
	if (!init_mutex(dinner))
		return (0);
	philo = &(dinner->philos[i]);
	while (i <  dinner->nbr_philos)
	{
		philo->id = i + 1;
		philo->last_meal = get_time();
		philo->meals_eaten = 0;
		philo->l_fork = i;
		philo->r_fork = (i + 1) % dinner->nbr_philos;
		philo->dinner = dinner;
		if (pthread_create(&(philo->tid), NULL, routine, philo))
			write(2, "Failed to create a philosopher thread !!\n", 42);
		else
		{
			if (pthread_detach(philo->tid))
				write(2, "Failed to detach a philosopher thread !!\n", 42);
		}
		i++;
	}
	return (1);
}

static int	check_arguments(int argc, char **argv, t_dinning *dinner)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid Arguments !!\n", 22), 0);
	dinner->nbr_philos = ft_atol(argv[1]);
	dinner->time2die = ft_atol(argv[2]);
	dinner->time2eat = ft_atol(argv[3]);
	dinner->time2sleep = ft_atol(argv[4]);
	dinner->nbr_meals = -1;
	if (!(argc ^ 6))
		dinner->nbr_meals = ft_atol(argv[5]);
	if (dinner->nbr_philos <= 0 || dinner->nbr_philos > 200)
		return (write(2, "Nbr of philos must be int between 1-200!!\n", 43), 0);
	if (dinner->time2die < 60)
		return (write(2, "T2D must be integer bigger than 60 ms!!\n", 41), 0);
	if (dinner->time2eat < 60)
		return (write(2, "T2E must be integer bigger than 60 ms!!\n", 41), 0);
	if (dinner->time2sleep < 60)
		return (write(2, "T2S must be integer bigger than 60 ms!!\n", 41), 0);
	if (argc == 6 && dinner->nbr_meals <= 0)
		return (write(2, "Nbr of meals must be int bigger than 1!!\n", 42), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_dinning	dinner;

	if (!check_arguments(argc, argv, &dinner))
		return (1);
	if (!init_dinner(&dinner))
		return (1);
	while(1);
	destroy_mutex(&dinner, FORK_M | PRINT_M | AUTHER_M, dinner.nbr_philos);
}
