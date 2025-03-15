/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:37:17 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/15 08:32:17 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	get_time(void)
{
	struct timeval	_time;

	if (gettimeofday(&_time, NULL) == -1)
	{
		write(2, "Failed to get the time of day !!\n", 34);
		return(-1);
	}
	return (_time.tv_sec * 1000 + _time.tv_usec / 1000);
}

void	precise_usleep(long msec, t_dinning *dinner)
{
	long	start;

	start = get_time();
	while (get_time() - start < msec && !get_dead_flag(dinner))
		usleep(500);
}
