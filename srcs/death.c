/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:23:17 by derblang          #+#    #+#             */
/*   Updated: 2023/08/04 13:20:43 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_deaths(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (is_dead(philo) == 1)
			return (1);
		while (i < philo->rules->nb_philo && philo->rules->argc == 6)
		{
			if (philo->meals_num > philo->rules->nb_of_meals)
			{
				philo->rules->all_eat++;
				if (philo->rules->all_eat == philo->rules->nb_philo)
				{
					print_msg(philo, TEXT_FINISH);
					return (1);
				}
			}
			i++;
		}
		usleep(500);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	if (get_the_time() - philo->last_meal > philo->rules->time_to_die)
	{
		print_msg(philo, TEXT_DEAD);
		return (1);
	}
	return (0);
}

void	destroy_mutex(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->death);
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}
