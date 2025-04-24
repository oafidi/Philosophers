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

/**
 * ft_strcmp - Compare deux chaînes de caractères.
 * Cette fonction compare les deux chaînes `s1` et `s2` et retourne une valeur négative,
 * zéro ou positive en fonction de la différence entre les deux chaînes.
 * Elle s'arrête dès qu'une différence est trouvée ou qu'une des chaînes se termine.
 *
 * @s1: Première chaîne à comparer.
 * @s2: Deuxième chaîne à comparer.
 *
 * Return: Un entier indiquant la différence entre les caractères correspondants
 *        des deux chaînes ou la fin de l'une d'entre elles.
 */
static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	// Compare les caractères tant qu'ils sont égaux et que les deux chaînes ne sont pas terminées
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	// Retourne la différence entre les deux caractères où la différence a été trouvée
	return (s1[i] - s2[i]);
}

/**
 * print - Affiche un message avec l'état du philosophe.
 * Cette fonction gère l'affichage des messages pour chaque philosophe en fonction de son état.
 * Si l'état est "died", la fonction verrouille le mutex pour éviter toute race condition
 * et affiche l'heure du décès avant de mettre à jour le flag de mort.
 * Pour d'autres messages, la fonction vérifie que le philosophe n'est pas mort avant d'afficher.
 *
 * @str: Le message à afficher.
 * @philo_id: L'identifiant du philosophe.
 * @dinner: Structure représentant le dîner (contenant, entre autres, le mutex d'affichage).
 */
void	print(char *str, int philo_id, t_dinning *dinner)
{
	// Si le message est "died", on gère le décès du philosophe
	if (!ft_strcmp(str, "died"))
	{
		// Verrouille le mutex d'affichage pour éviter la concurrence lors de l'impression
		pthread_mutex_lock(&dinner->print);
		// Affiche l'heure du décès du philosophe
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
		// Met à jour le flag de mort pour signaler que le philosophe est mort
		set_dead_flag(dinner, 1);
		// Une petite pause pour garantir que le message est bien imprimé avant de continuer
		usleep(50);
		// Déverrouille le mutex d'affichage
		pthread_mutex_unlock(&dinner->print);
		return ;
	}
	
	// Si le philosophe n'est pas mort, on affiche son état
	pthread_mutex_lock(&dinner->print);
	// Vérifie si le dîner n'a pas encore pris fin (philosophe mort)
	if (!get_dead_flag(dinner))
		// Affiche l'état du philosophe avec l'heure écoulée depuis le début du dîner
		printf("%ld %d %s\n", get_time() - dinner->start_time, philo_id, str);
	// Déverrouille le mutex d'affichage
	pthread_mutex_unlock(&dinner->print);
}
