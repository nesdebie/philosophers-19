/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:08 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 11:46:24 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	end_condition_reached(t_rules *rules, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (get_time_in_ms() - philo->last_meal >= rules->time_to_die)
	{
		print_action(philo, 1, DIED);
		sem_post(rules->this_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (EXIT_FAILURE);
	}
	if (rules->must_eat_count != -1 && !philo->ate_enough
		&& philo->times_ate >= (unsigned int)rules->must_eat_count)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = 1;
	}
	sem_post(philo->sem_meal);
	return (EXIT_SUCCESS);
}

static void	*process_waiter(void *data)
{
	t_rules			*rules;

	rules = (t_rules *)data;
	if (!rules->must_eat_count)
		return (0);
	sem_wait(rules->this_philo->sem_philo_dead);
	sem_wait(rules->this_philo->sem_philo_full);
	sim_start_delay(rules->start_time);
	while (!end_condition_reached(rules, rules->this_philo))
	{
		usleep(1000);
		continue ;
	}
	return (0);
}

static int	open_semaphores2(t_philo *philo)
{
	philo->sem_forks = sem_open("forks", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_forks == (sem_t *)-1)
		return (EXIT_FAILURE);
	philo->sem_write = sem_open("write", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == (sem_t *)-1)
		return (EXIT_FAILURE);
	philo->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_full == (sem_t *)-1)
		return (EXIT_FAILURE);
	philo->sem_philo_dead = sem_open("dead", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_dead == (sem_t *)-1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	open_semaphores(t_rules *rules, t_philo *philo)
{
	if (rules->nb_philos == 1)
		return ;
	if (open_semaphores2(philo))
		child_exit(rules, ERR_SEM);
	if (pthread_create(&philo->p_killer, NULL, &process_waiter, rules))
		child_exit(rules, ERR_PTHREAD);
}
