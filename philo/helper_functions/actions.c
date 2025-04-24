/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:39 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/20 08:52:50 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/**
 * sleep_action - Gère l'action de dormir d'un philosophe.
 * Le philosophe s'endort pendant une période de temps spécifiée.
 * La fonction vérifie si le flag de mort n'est pas activé avant d'effectuer l'action.
 *
 * @philo: Pointeur vers la structure représentant le philosophe.
 */
void sleep_action(t_philosopher *philo)
{
    if (!get_dead_flag(philo->dinner))
    {
        // Affiche que le philosophe est en train de dormir
        print("is sleeping", philo->id, philo->dinner);
        
        // Le philosophe dort pendant le temps spécifié
        precise_usleep(philo->dinner->time2sleep, philo->dinner);
    }
}

/**
 * eat_action - Gère l'action de manger d'un philosophe.
 * Le philosophe prend deux fourchettes, mange pendant un certain temps, 
 * puis repose les fourchettes. La fonction vérifie si le philosophe est mort avant de commencer.
 *
 * @philo: Pointeur vers la structure représentant le philosophe.
 */
void eat_action(t_philosopher *philo)
{
    if (!get_dead_flag(philo->dinner))
    {
        // Prend la première fourchette
        pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
        print("has taken a fork", philo->id, philo->dinner);

        // Prend la seconde fourchette
        pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
        print("has taken a fork", philo->id, philo->dinner);

        // Affiche que le philosophe mange
        print("is eating", philo->id, philo->dinner);

        // Mets à jour le nombre de repas mangés et l'heure du dernier repas
        pthread_mutex_lock(&philo->dinner->meals);
        philo->meals_eaten++;
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->dinner->meals);

        // Le philosophe mange pendant le temps spécifié
        precise_usleep(philo->dinner->time2eat, philo->dinner);

        // Repose les fourchettes
        pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
        pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
    }
}

/**
 * think_action - Gère l'action de penser d'un philosophe.
 * Le philosophe affiche qu'il est en train de penser. 
 * La fonction vérifie si le flag de mort n'est pas activé avant de commencer l'action.
 *
 * @philo: Pointeur vers la structure représentant le philosophe.
 */
void think_action(t_philosopher *philo)
{
    if (!get_dead_flag(philo->dinner))
        // Affiche que le philosophe est en train de penser
        print("is thinking", philo->id, philo->dinner);
}
