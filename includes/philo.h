/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:22:45 by derblang          #+#    #+#             */
/*   Updated: 2023/08/04 13:22:49 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TEXT_FORK "\033[33m has taken a fork \033[0m"
# define TEXT_EAT "\033[32m is eating \033[0m"
# define TEXT_SLEEP "\033[34m is sleeping \033[0m"
# define TEXT_THINK "\033[35m is thinking \033[0m"
# define TEXT_DEAD "\033[31m is died \033[0m"
# define TEXT_FINISH "\033[36m all the philosophers have eaten! \033[0m"

typedef struct s_rules
{
	int				argc;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo;
	int				nb_of_meals;
	int				all_eat;
	long long		time;
	pthread_mutex_t	msg;
}					t_rules;

typedef struct s_philo
{
	pthread_t		aristo;
	int				id;
	int				meals_num;
	int				right_fork;
	int				left_fork;
	long long		last_meal;
	t_rules			*rules;
	pthread_mutex_t	death;
	pthread_mutex_t	*fork;
}					t_philo;

//Main
void				philo_init(t_rules *rules);
int					init_all(t_philo *philo, t_rules *rules,
						pthread_mutex_t *fork);

//Check_args
int					check_args(int argc, char **argv);

//Routine

void				think(t_philo *philo);
int					ft_eat(t_philo *philo);
void				*only_one(t_philo *philo);
int					thread_join(t_philo *philo);
void				*routine(void *param);

//Utils
int					ft_atoi(const char *nptr);
int					put_error(const char *msg);
void				free_all(t_philo *philo, pthread_mutex_t *fork);

//Time
long long			get_the_time(void);
void				ft_sleep(int time);
void				print_msg(t_philo *philo, char *message);

//Death
void				destroy_mutex(t_philo *philo, pthread_mutex_t *fork);
int					check_deaths(t_philo *philo);
int					is_dead(t_philo *philo);

#endif