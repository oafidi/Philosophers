/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:40:45 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/21 10:57:12 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// Cas spécial pour un seul philosophe : prend une fourchette puis finit
void one_philo(t_philosopher *philo)
{
    if (!get_dead_flag(philo->dinner))
    {
        pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
        print("has taken a fork", philo->id, philo->dinner);
        pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
    }
}

// Initialise chaque philosophe
static void init_philosopher(t_dinning *dinner)
{
    int i = 0;
    t_philosopher *philo;

    while (i < dinner->nbr_philos)
    {
        philo = &(dinner->philos[i]);
        philo->id = i + 1;
        pthread_mutex_lock(&dinner->meals);
        philo->last_meal = get_time();
        philo->meals_eaten = 0;
        pthread_mutex_unlock(&dinner->meals);
        philo->l_fork = i;
        philo->r_fork = (i + 1) % dinner->nbr_philos;
        philo->dinner = dinner;
        i++;
    }
}

// Crée les threads des philosophes
static int create_philosophers(t_dinning *dinner)
{
    int i = 0;
    t_philosopher *philo;

    while (i < dinner->nbr_philos)
    {
        philo = &(dinner->philos[i]);
        pthread_mutex_lock(&dinner->meals);
        philo->last_meal = get_time();
        pthread_mutex_unlock(&dinner->meals);
        if (pthread_create(&(philo->tid), NULL, routine, philo))
        {
            set_dead_flag(dinner, 1);
            write(2, "Failed to create a philosopher thread !!\n", 42);
            return (i);
        }
        i++;
    }
    return (i);
}

// Attend la fin de tous les threads des philosophes
static void join_philosophers(t_dinning *dinner, int count)
{
    int i = 0;

    while (i < count)
    {
        if (pthread_join(dinner->philos[i].tid, NULL))
        {
            set_dead_flag(dinner, 1);
            write(2, "Failed to detach a philo thread !!\n", 36);
        }
        i++;
    }
}

// Fonction principale d'initialisation : mutex, philosophes, threads
int init_dinner(t_dinning *dinner)
{
    int count;

    if (!init_mutex(dinner))
        return (0);
    dinner->start_time = get_time();
    set_dead_flag(dinner, 0);
    init_philosopher(dinner);

    // Création du superviseur
    if (pthread_create(&dinner->supervisor, NULL, supervisor, dinner))
        return (write(2, "Failed to create supervisor thread !!\n", 39), 0);

    // Création des philosophes
    count = create_philosophers(dinner);

    // Attente de fin du superviseur
    if (pthread_join(dinner->supervisor, NULL))
    {
        set_dead_flag(dinner, 1);
        write(2, "Failed to detach supervisor thread !!\n", 39);
    }

    // Attente de fin des philosophes
    join_philosophers(dinner, count);
    return (1);
}
