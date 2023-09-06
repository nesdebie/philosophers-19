/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:42:36 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 15:05:13 by nesdebie         ###   ########.fr       */
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

# define WRONG_ARGS 1
# define MUTEX_FAIL 2
# define MALLOC_FAIL 3

# define OVERFLOW 2147483647

typedef struct s_philosopher
{
	int					id;
	int					is_fed;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meals;
	int					dead;
	int					all_fed;
	time_t				start_time;
	pthread_mutex_t		state_write;
	pthread_mutex_t		*forks;
	t_philosopher		*phi;
}						t_rules;

/* ERROR */
int		ft_error(char *str);

/* INIT AND CHECK */
int		init_manager(t_rules *rules, char **av);

/* EVENT PRINTER */
void	print_routine(t_rules *rules, int id, char *string);

/* THREADS */
int		philo_threads(t_rules *rules);

/* TIME */
time_t	get_time(void);
void	better_usleep(time_t time, t_rules *rules);

/* LIBFT */
int		philo_atoi(char *str);

#endif