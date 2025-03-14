/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:30 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/12 06:50:52 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_dinning	dinner;

	if (!check_arguments(argc, argv, &dinner))
		return (1);
	if (!init_dinner(&dinner))
		return (1);
	while(1);
	destroy_mutex(&dinner, FORK_M | PRINT_M | AUTHER_M, dinner.nbr_philos);
}
