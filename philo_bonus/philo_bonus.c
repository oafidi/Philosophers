/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:05 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/22 13:41:04 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_dinning	dinner;
	int			count;

	if (!check_arguments(argc, argv, &dinner))
		return (1);
	if (!init_dinner(&dinner))
		return (1);
	count = create_philosophers(&dinner);
	sem_wait(dinner.stop);
	kill_processes(&dinner, count);
	destroy_semaphores(&dinner);
}
