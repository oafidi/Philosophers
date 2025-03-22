/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:22:44 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 10:52:22 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_dinner(t_dinning *dinner)
{
	if (!init_semaphores(dinner))
		return (0);
	dinner->start_time = get_time();
	
}