/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:21:50 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/15 06:27:46 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print(char *str, int philo_id, t_dinning *dinner)
{
	if (!get_dead_flag(dinner))
	{
		pthread_mutex_lock(&dinner->print);
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
		pthread_mutex_unlock(&dinner->print);
	}
}