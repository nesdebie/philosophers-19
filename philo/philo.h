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
	long long			first_timestamp;
	pthread_mutex_t		state_write;
	pthread_mutex_t		forks[250];
	t_philosopher		phi[250];
}						t_rules;

int						ft_error(char *str);

int						init_manager(t_rules *rules, char **argv);

size_t					ft_strlen(char const *str);
int						ft_atoi(char const *str);
void					print_routine(t_rules *rules, int id, char *string);
long long				get_time(void);
void					better_usleep(long long time, t_rules *rules);

int						launcher(t_rules *rules);

#endif