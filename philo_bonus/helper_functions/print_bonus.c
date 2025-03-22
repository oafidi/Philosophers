/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:55:55 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/22 15:15:33 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
		sem_wait(dinner->print);
		sem_wait(dinner->meals);
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
		sem_post(dinner->stop);
		return ;
	}
	sem_wait(dinner->print);
	printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
	sem_post(dinner->print);
}
