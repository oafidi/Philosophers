/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:41:43 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/20 08:55:26 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/**
 * get_dead_flag - Récupère l'état de mort du dîner.
 * Cette fonction accède de manière thread-safe à la variable `is_dead` de la structure
 * `dinner` pour déterminer si le dîner est terminé (si un philosophe est mort).
 * Elle utilise un mutex pour garantir l'accès exclusif à cette variable.
 *
 * @dinner: La structure représentant l'état du dîner.
 *
 * Return: La valeur de `is_dead` indiquant si un philosophe est mort (1) ou non (0).
 */
int	get_dead_flag(t_dinning *dinner)
{
	int	dead;

	// Verrouille le mutex pour accéder en toute sécurité à la variable `is_dead`
	pthread_mutex_lock(&dinner->dead);
	dead = dinner->is_dead;
	// Déverrouille le mutex une fois que la lecture est effectuée
	pthread_mutex_unlock(&dinner->dead);
	return (dead);
}

/**
 * set_dead_flag - Définit l'état de mort du dîner.
 * Cette fonction permet de mettre à jour la variable `is_dead` dans la structure
 * `dinner` pour signaler qu'un philosophe est mort. Elle verrouille un mutex
 * afin d'éviter les accès concurrents à cette variable.
 *
 * @dinner: La structure représentant l'état du dîner.
 * @value: La valeur à affecter à la variable `is_dead` (0 pour vivant, 1 pour mort).
 */
void	set_dead_flag(t_dinning *dinner, int value)
{
	// Verrouille le mutex pour accéder de manière sécurisée à `is_dead`
	pthread_mutex_lock(&dinner->dead);
	dinner->is_dead = value;
	// Déverrouille le mutex après la mise à jour de la variable
	pthread_mutex_unlock(&dinner->dead);
}

/**
 * have_eating - Vérifie si tous les philosophes ont mangé un nombre suffisant de repas.
 * Cette fonction vérifie pour chaque philosophe si le nombre de repas qu'il a consommés
 * a atteint ou dépassé `nbr_meals`. Si tous les philosophes ont mangé suffisamment,
 * la fonction retourne `true`, sinon elle retourne `false`.
 *
 * @dinner: La structure représentant l'état du dîner.
 *
 * Return: 1 si tous les philosophes ont mangé suffisamment de repas, sinon 0.
 */
static int	have_eating(t_dinning *dinner)
{
	int	i;
	int	count;
	int	meals_eaten;

	count = 0;
	i = 0;
	// Parcours de tous les philosophes
	while (i < dinner->nbr_philos)
	{
		// Verrouille l'accès au nombre de repas pour éviter les accès concurrents
		pthread_mutex_lock(&dinner->meals);
		meals_eaten = dinner->philos[i].meals_eaten;
		pthread_mutex_unlock(&dinner->meals);
		// Si le philosophe a mangé assez de repas, on l'ajoute au compteur
		if (dinner->nbr_meals <= meals_eaten)
			count++;
		i++;
	}
	// Retourne si tous les philosophes ont mangé assez
	return (count == dinner->nbr_philos);
}

/**
 * supervisor - Fonction supervisant l'état du dîner.
 * Le superviseur vérifie périodiquement l'état de chaque philosophe pour s'assurer
 * que personne n'est mort ou que tous ont mangé suffisamment de repas. Si un philosophe
 * est mort ou que tous ont mangé, la fonction met à jour le flag `is_dead` et termine le dîner.
 *
 * @arg: L'argument passé à la fonction, ici un pointeur vers la structure `dinning`.
 *
 * Return: Retourne NULL lorsque le dîner est terminé, soit en raison d'un philosophe mort
 *         ou du fait que tous les repas ont été mangés.
 */
void	*supervisor(void *arg)
{
	int				i;
	long			last_time;
	t_philosopher	*philo;
	t_dinning		*dinner;

	dinner = (t_dinning *)arg;
	while (1)
	{
		// Si tous les philosophes ont mangé le nombre de repas nécessaire
		if (dinner->nbr_meals && have_eating(dinner))
			return (set_dead_flag(dinner, 1), NULL);
		i = 0;
		while (i < dinner->nbr_philos)
		{
			philo = &dinner->philos[i];
			// Verrouille l'accès au dernier repas du philosophe
			pthread_mutex_lock(&dinner->meals);
			last_time = philo->last_meal; 
			pthread_mutex_unlock(&dinner->meals);
			// Si un philosophe n'a pas mangé depuis trop longtemps (temps dépassé)
			if (get_time() - last_time > dinner->time2die) 
				return (print("died", i + 1, dinner), NULL);
			i++;
		}
		// Met en pause le superviseur pendant une courte période avant de vérifier à nouveau
		usleep(500);
	}
}

/**
 * routine - Routine principale d'un philosophe.
 * Cette fonction gère le cycle de vie d'un philosophe, consistant en dormir, manger
 * et réfléchir. Si le philosophe est seul, il suit un comportement spécifique.
 * Chaque philosophe alterne entre manger, dormir et penser jusqu'à ce qu'il soit mort.
 *
 * @arg: L'argument passé à la fonction, ici un pointeur vers un philosophe.
 *
 * Return: Retourne NULL lorsque le philosophe meurt ou lorsqu'il termine son cycle.
 */
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	// Si un philosophe est seul, il exécute une routine particulière
	if (philo->dinner->nbr_philos == 1)
		return (one_philo(philo), NULL);
	// Si l'ID du philosophe est impair, il mange en premier
	if (philo->id % 2 == 1)
		eat_action(philo);
	// Exécute la routine complète pour chaque philosophe jusqu'à ce qu'il meurt
	while (!get_dead_flag(philo->dinner))
	{
		sleep_action(philo);
		think_action(philo);
		eat_action(philo);
	}
	return (NULL);
}
