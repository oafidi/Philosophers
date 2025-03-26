/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:30 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/16 00:59:57 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_dinning	dinner;

	if (!check_arguments(argc, argv, &dinner))//3la wed parsing
		return (1);
	if (!init_dinner(&dinner))//hna kaybda le3cha
		return (1);
	destroy_mutex(&dinner, FORK | PRINT | DEAD | MEAL, dinner.nbr_philos);//flekher khas ndir destroy lga3 mutex dyali
}
