/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oafidi <oafidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:36:43 by oafidi            #+#    #+#             */
/*   Updated: 2025/03/10 05:10:59 by oafidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static long	ft_atol(char *str)
{
	int		i;
	long	nbr;

	nbr = 0;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			return (-1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i++] - 48);
		if (nbr > INT_MAX)
			return (-1);
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (-1);
	return (nbr);
}

int	check_arguments(int argc, char **argv, t_dinning *dinner)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Invalid Arguments !!\n", 22), 0);
	dinner->nbr_philos = ft_atol(argv[1]);
	dinner->time2die = ft_atol(argv[2]);
	dinner->time2eat = ft_atol(argv[3]);
	dinner->time2sleep = ft_atol(argv[4]);
	dinner->nbr_meals = -1;
	if (!(argc ^ 6))
		dinner->nbr_meals = ft_atol(argv[5]);
	if (dinner->nbr_philos <= 0 || dinner->nbr_philos > 200)
		return (write(2, "Nbr of philos must be int between 1-200!!\n", 43), 0);
	if (dinner->time2die < 60)
		return (write(2, "T2D must be integer bigger than 60 ms!!\n", 41), 0);
	if (dinner->time2eat < 60)
		return (write(2, "T2E must be integer bigger than 60 ms!!\n", 41), 0);
	if (dinner->time2sleep < 60)
		return (write(2, "T2S must be integer bigger than 60 ms!!\n", 41), 0);
	if (argc == 6 && dinner->nbr_meals <= 0)
		return (write(2, "Nbr of meals must be int bigger than 1!!\n", 42), 0);
	return (1);
}
