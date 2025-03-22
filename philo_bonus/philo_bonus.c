/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:05 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 10:01:29 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_dinning	dinner;

	if (!check_arguments(argc, argv, &dinner))
		return (1);
	if (!init_dinner(&dinner))
		return (1);
}