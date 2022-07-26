/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:19:33 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/26 12:20:00 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_philo_meals;
	int					dead;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		phi[250];
}						t_rules;

int						ft_error(char *str);

int						init_manager(t_rules *rules, char **argv);

size_t					ft_strlen(char const *str);
int						ft_atoi(char const *str);
void					print_routine(t_rules *rules, int id, char *string);
long long				timestamp(void);
void					philo_sleep(long long time, t_rules *rules);

int						launcher(t_rules *rules);

#endif