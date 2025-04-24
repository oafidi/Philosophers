/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:37:17 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/18 23:24:53 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/**
 * get_time - Obtient le temps actuel en millisecondes depuis l'époque Unix.
 * Cette fonction utilise `gettimeofday` pour récupérer le temps actuel avec
 * une précision de millisecondes, en renvoyant le temps écoulé depuis le 1er janvier 1970
 * (l'époque Unix).
 * En cas d'erreur lors de la récupération du temps, un message d'erreur est affiché
 * et la fonction retourne 0.
 *
 * Return: Le temps actuel en millisecondes, ou 0 en cas d'erreur.
 */
long	get_time(void)
{
	struct timeval	_time;

	// Récupère l'heure actuelle en microsecondes
	if (gettimeofday(&_time, NULL) == -1)
	{
		write(2, "Failed to get the time of day !!\n", 34);
		return (0); // Si l'appel échoue, retourne 0
	}
	// Convertit le temps en millisecondes (tv_sec est en secondes, tv_usec en microsecondes)
	return (_time.tv_sec * 1000 + _time.tv_usec / 1000);
}

/**
 * precise_usleep - Pause le programme pendant un nombre de millisecondes spécifié.
 * Cette fonction suspend l'exécution du programme pendant le nombre de millisecondes
 * spécifié par `msec`. La fonction s'assure également que le dîner n'a pas été
 * interrompu en vérifiant régulièrement l'état de mort du dîner. Elle utilise
 * `usleep` pour effectuer des pauses de 100 microsecondes, permettant un contrôle
 * plus fin de l'attente.
 *
 * @msec: Le nombre de millisecondes pendant lesquelles la fonction doit dormir.
 * @dinner: La structure représentant l'état du dîner, utilisée pour vérifier si
 *          le dîner a été interrompu (par exemple, si un philosophe est mort).
 */
void	precise_usleep(long msec, t_dinning *dinner)
{
	long	start;

	start = get_time(); // Récupère l'heure de départ
	// Boucle de sommeil jusqu'à ce que le temps écoulé dépasse msec ou jusqu'à la mort d'un philosophe
	while (get_time() - start < msec && !get_dead_flag(dinner))
		usleep(100); // Attendre par petites périodes de 100 microsecondes
}

