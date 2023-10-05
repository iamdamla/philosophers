/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:16:53 by derblang          #+#    #+#             */
/*   Updated: 2023/08/07 09:39:44 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	rules_init(t_rules *rules, char **argv, int argc)
{
	rules->argc = argc;
	rules->all_eat = 0;
	rules->time = 0;
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->nb_of_meals = ft_atoi(argv[5]);
	else
		rules->nb_of_meals = -1;
}

static int	forks_init(t_philo *philo, t_rules *rules, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&philo[i].death, NULL) != 0)
		return (1);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_all(t_philo *philo, t_rules *rules, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % rules->nb_philo;
		philo[i].meals_num = 0;
		philo[i].last_meal = rules->time;
		philo[i].rules = rules;
		philo[i].fork = fork;
		if (pthread_create(&philo[i].aristo, NULL, &routine, &philo[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

int	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		if (pthread_detach(philo[i++].aristo) != 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (check_args(argc, argv) == 1)
		return (0);
	rules_init(&rules, argv, argc);
	rules.time = get_the_time();
	philo = malloc(sizeof(t_philo) * rules.nb_philo);
	fork = malloc(sizeof(pthread_mutex_t) * rules.nb_philo);
	if (forks_init(philo, &rules, fork) == 1)
		put_error("problem with mutex\n");
	if (init_all(philo, &rules, fork) == 1)
		put_error("problem with threads\n");
	if (thread_join(philo) == 1)
		put_error("problem with pthread_join\n");
	if (check_deaths(philo) == 1)
	{
		destroy_mutex(philo, fork);
		free_all(philo, fork);
	}
	return (0);
}
