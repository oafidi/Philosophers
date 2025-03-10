/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:30 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/10 06:13:04 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(int argc, char **argv, t_dinning	*table)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid Arguments !!\n", 22), 0);
	table->nbr_philos = ft_atol(argv[1]);
	table->time2die = ft_atol(argv[2]);
	table->time2eat = ft_atol(argv[3]);
	table->time2sleep = ft_atol(argv[4]);
	table->nbr_meals = 0;
	if (!(argc ^ 6))
		table->nbr_meals = ft_atol(argv[5]);
	printf("%d %ld %ld %ld %d \n", table->nbr_philos, ft_atol(argv[2]), table->time2eat, table->time2sleep, table->nbr_meals);
	if (table->nbr_philos <= 0 || table->nbr_philos > 200)
		return (write(2, "Nbr of philos must be int between 1-200!!\n", 41), 0);
	if (table->time2die < 60)
		return (write(2, "T2D must be integer bigger than 60 ms!!\n", 41), 0);
	if (table->time2eat < 60)
		return (write(2, "T2E must be integer bigger than 60 ms!!\n", 41), 0);
	if (table->time2sleep < 60)
		return (write(2, "T2S must be integer bigger than 60 ms!!\n", 42), 0);
	if (argc == 6 && table->nbr_meals < 1)
		return (write(2, "Nbr of meals must be int bigger than 1!!\n", 33), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_dinning	table;

	if (!check_arguments(argc, argv, &table))
		return (1);
}
