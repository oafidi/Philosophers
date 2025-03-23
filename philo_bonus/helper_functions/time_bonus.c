/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:53:27 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/23 11:19:34 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

long	get_time(void)
{
	struct timeval	_time;

	if (gettimeofday(&_time, NULL) == -1)
	{
		write(2, "Failed to get the time of day !!\n", 34);
		return (0);
	}
	return (_time.tv_sec * 1000 + _time.tv_usec / 1000);
}

void	precise_usleep(long msec)
{
	long	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(100);
}
