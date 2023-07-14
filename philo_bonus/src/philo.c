/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:45:26 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 14:38:46 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	eat_sleep_routine(t_philo *philo)
{
	grab_fork(philo);
	grab_fork(philo);
	print_action_parser(philo, 0, EATING);
	sem_wait(philo->sem_meal);
	philo->last_meal = get_time_in_ms();
	sem_post(philo->sem_meal);
	philo_sleep(philo->rules->time_to_eat);
	print_action_parser(philo, 0, SLEEPING);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_meal);
	philo->nb_forks_held -= 2;
	philo->times_ate += 1;
	sem_post(philo->sem_meal);
	philo_sleep(philo->rules->time_to_sleep);
}

static void	think_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	sem_wait(philo->sem_meal);
	time_to_think = (philo->rules->time_to_die
			- (get_time_in_ms() - philo->last_meal)
			- philo->rules->time_to_eat) / 2;
	sem_post(philo->sem_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == 0)
		print_action_parser(philo, 0, THINKING);
	philo_sleep(time_to_think);
}

static void	lone_philo_routine(t_philo *philo)
{
	philo->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_full == (sem_t *)-1)
		exit(EXIT_FAILURE);
	sem_wait(philo->sem_philo_full);
	sim_start_delay(philo->rules->start_time);
	if (philo->rules->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(FULL);
	}
	print_action(philo, "has taken a fork");
	philo_sleep(philo->rules->time_to_die);
	print_action(philo, "died");
	free_rules(philo->rules);
	exit(DIED);
}

static void	philosopher_routine(t_philo *philo)
{
	if (philo->id % 2)
		think_routine(philo, 1);
	while (1)
	{
		eat_sleep_routine(philo);
		think_routine(philo, 0);
	}
}

void	philosopher(t_rules *rules)
{
	t_philo	*philo;

	philo = rules->this_philo;
	if (philo->rules->nb_philos == 1)
		lone_philo_routine(philo);
	init_philo_ipc(rules, philo);
	if (philo->rules->must_eat_count == 0)
	{
		sem_post(philo->sem_philo_full);
		child_exit(rules, FULL);
	}
	if (philo->rules->time_to_die == 0)
	{
		sem_post(philo->sem_philo_dead);
		child_exit(rules, DIED);
	}
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->rules->start_time;
	sem_post(philo->sem_meal);
	sim_start_delay(philo->rules->start_time);
	philosopher_routine(philo);
}
