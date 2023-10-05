/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:24:18 by derblang          #+#    #+#             */
/*   Updated: 2023/08/04 13:17:11 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\f')
		return (8);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int		counter;
	int		res;
	char	*charptr;

	counter = 0;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if ((*nptr && *nptr == '-' && counter++ == 0) || (*nptr && *nptr == '+'))
		nptr++;
	charptr = (char *)nptr;
	while ((*charptr >= '0' && *charptr <= '9'))
		charptr++;
	if (counter == 0 && (charptr - nptr) > 10)
		return (-1);
	else if (counter == 1 && (charptr - nptr) > 11)
		return (0);
	while ((*nptr >= '0' && *nptr <= '9') && *nptr)
		res = res * 10 + (*nptr++ - '0');
	if (counter == 1)
		res *= -1;
	return (res);
}

static void	ft_putendl_fd(const char *str, int fd)
{
	if (fd >= 0)
	{
		while (*str)
		{
			write(fd, &*str, 1);
			str++;
		}
		write(1, "\n", fd);
	}
}

int	put_error(const char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}

void	free_all(t_philo *philo, pthread_mutex_t *fork)
{
	free(philo);
	free(fork);
}
