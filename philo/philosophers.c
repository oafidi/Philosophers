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

// Fonction principale qui initialise le programme
int main(int argc, char **argv)
{
    t_dinning dinner;

    // Vérifie les arguments et les enregistre dans la structure dinner
    if (!check_arguments(argc, argv, &dinner))
        return (1);

    // Initialise les structures, les threads et les mutex
    if (!init_dinner(&dinner))
        return (1);

    // Libère les ressources (mutex) allouées
    destroy_mutex(&dinner, FORK | PRINT | DEAD | MEAL, dinner.nbr_philos);
}
