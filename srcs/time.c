/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:11:42 by derblang          #+#    #+#             */
/*   Updated: 2023/08/04 13:18:07 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_the_time(void)
{
	struct timeval	now;
	long			sec;
	long			usec;
	long long		ms;

	gettimeofday(&now, NULL);
	sec = now.tv_sec;
	usec = now.tv_usec;
	ms = (sec * 1000) + (usec / 1000);
	return (ms);
}

void	ft_sleep(int time)
{
	struct timeval	a;
	struct timeval	b;

	gettimeofday(&b, NULL);
	gettimeofday(&a, NULL);
	while (((a.tv_sec - b.tv_sec) * 1000 + (a.tv_usec - b.tv_usec)
			/ 1000) < time)
	{
		usleep(500);
		gettimeofday(&a, NULL);
	}
}

void	print_msg(t_philo *philo, char *message)
{
	struct timeval	now;

	pthread_mutex_lock(&philo->rules->msg);
	gettimeofday(&now, NULL);
	printf("%lld ms Philo %d  %s\n", get_the_time() - philo->rules->time,
		philo->id + 1, message);
	pthread_mutex_unlock(&philo->rules->msg);
}
