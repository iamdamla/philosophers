/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:37:36 by derblang          #+#    #+#             */
/*   Updated: 2023/08/04 13:16:41 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	ft_strtolol(const char *str)
{
	size_t		i;
	long long	res;
	int			sign;

	res = 0;
	i = 0;
	sign = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && '0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res * sign > 2147483647)
			return (0);
		else if (res * sign < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_strtolol(argv[i]) || !ft_isnumber(argv[i]))
			return (put_error("Error: Invalid arguments!"));
		i++;
	}
	if (argc < 5 || argc > 6)
		return (put_error("Error: Number of arguments is incorrect!"));
	if (ft_atoi(argv[1]) <= 0)
		return (put_error("Error: There are no philosophers!"));
	return (0);
}
