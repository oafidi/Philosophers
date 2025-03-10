#include "../philosophers.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	nbr;

	nbr = 0;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i++]));
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		if (nbr > INT_MAX)
			return (-1);
		i++;
	}
	while (ft_isspace(str[i++]));
	if (!str[i])
		return (-1);
	return (nbr);
}
