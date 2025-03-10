/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:30 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/10 02:52:15 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg);

static int	init_table(t_dinning *dinner)
{
	int	i;

	i = 0;
	if (!init_mutex(dinner))
		return (0);
	while (i <  dinner->nbr_philos)
	{
		dinner->philos[i].id = i + 1;
		dinner->philos[i].start_time = get_time();
		dinner->philos[i].meals_eaten = 0;
		if (pthread_create(&dinner->philos[i].tid, NULL, routine, dinner))
			write(2, "Failed to create a philosopher !!\n", 35);
		else
		{
			if (pthread_detach(dinner->philos[i].tid))
				write(2, "Failed to detach a philosopher !!\n", 35);
		}
		i++;
	}
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
	if (!init_table(&dinner))
		return (1);
}
