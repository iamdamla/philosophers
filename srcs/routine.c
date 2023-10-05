/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:36:23 by derblang          #+#    #+#             */
/*   Updated: 2023/08/07 09:42:35 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_eat(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->left_fork]);
		pthread_mutex_lock(&philo->fork[philo->right_fork]);
		pthread_mutex_lock(&philo->death);
		print_msg(philo, TEXT_FORK);
		print_msg(philo, TEXT_FORK);
		print_msg(philo, TEXT_EAT);
		philo->last_meal = get_the_time();
		philo->meals_num++;
		ft_sleep(philo->rules->time_to_eat);
		pthread_mutex_unlock(&philo->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->death);
		print_msg(philo, TEXT_SLEEP);
		ft_sleep(philo->rules->time_to_sleep);
		print_msg(philo, TEXT_THINK);
	}
	return (0);
}

void	*only_one(t_philo *philo)
{
	if (philo->rules->nb_philo == 1)
		print_msg(philo, TEXT_FORK);
	return (NULL);
}

void	ft_think(t_philo *philo)
{
	print_msg(philo, TEXT_THINK);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		if (philo->rules->nb_philo == 1)
			only_one(philo);
		ft_eat(philo);
		ft_think(philo);
	}
}
