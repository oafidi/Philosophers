/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:21:50 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/12 06:35:05 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	print(char *str, int philo_id, t_dinning *dinner)
{
	pthread_mutex_lock(&dinner->print);
	printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
	pthread_mutex_unlock(&dinner->print);
}