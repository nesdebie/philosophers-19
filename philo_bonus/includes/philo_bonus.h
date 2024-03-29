/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:42:36 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/19 15:32:20 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>
# include <stdatomic.h>

# define DIED 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define FORK_1 4
# define FORK_2 5
# define FULL 6

# define ERR_PTHREAD 7
# define ERR_SEM 8

# define OVERFLOW 2147483647

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	time_t			start_time;
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	unsigned int	philo_full_count;
	sem_t			*sem_philo_dead;
	sem_t			*sem_stop;
	atomic_int		stop;
	t_philo			**philos;
	t_philo			*this_philo;
	pid_t			*pids;
	pthread_t		fed;
	pthread_t		dead;
}	t_rules;

typedef struct s_philo
{
	pthread_t		p_killer;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	sem_t			*sem_philo_dead;
	sem_t			*sem_meal;
	unsigned int	nb_forks_held;
	unsigned int	id;
	atomic_uint		times_ate;
	int				ate_enough;
	atomic_long		last_meal;
	t_rules			*rules;
}	t_philo;

/* PARENT */
int		philo_stop(t_rules	*rules);

/* CHILD */
void	philosopher(t_rules *rules);

/* CHECKERS */
int		is_stopped(t_rules *rules);
int		is_valid(int ac, char **av);

/* INIT */
t_rules	*init_rules(int ac, char **av);
void	open_semaphores(t_rules *rules, t_philo *philo);

void	unlink_global_sems(void);

/* TIME */
time_t	get_time(void);
void	philo_sleep(time_t sleep_time);
void	sim_start_delay(time_t start_time);

/* PRINTER */
void	print_action(t_philo *philo, int end_flag, int status);

/* KILLERS */
void	*ft_all_fed(void *data);
void	*ft_starve_to_death(void *data);
int		kill_all_philos(t_rules *rules, int exit_code);

/* LIBFT */
int		philo_atoi(char *str);

/* FREES */
void	*free_rules(t_rules *rules);
int		sem_error_cleanup(t_rules *rules);

/* ERRORS */
void	child_exit(t_rules *rules, int exit_code);
int		error_msg(char *str, int exit_nb);
int		ft_error(char *str, t_rules *rules);
void	*error_null(char *str, t_rules *rules);
int		rules_cleanup(t_rules *rules, int exit_code);

#endif