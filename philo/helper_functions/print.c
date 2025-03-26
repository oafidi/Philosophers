/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:21:50 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/20 08:54:52 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print(char *str, int philo_id, t_dinning *dinner)
{
	if (!ft_strcmp(str, "died"))
	{
		pthread_mutex_lock(&dinner->print);
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
		set_dead_flag(dinner, 1); // ila ktebt message dyal die kan9oul lphilos bli wa7ed mat bach y7ebsso routine
		usleep(50);
		pthread_mutex_unlock(&dinner->print);
		return ;
	}
	pthread_mutex_lock(&dinner->print);// sed 3la stdin
	if (!get_dead_flag(dinner))
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str); //kteb
	pthread_mutex_unlock(&dinner->print);// tlo9 l mutex
}
