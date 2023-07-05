/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:54 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:11:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* kill_all_philos:
*	Sends the kill signal to all philosopher processes. Used to send the
*	simulation if a philosopher has died or if a philosopher process has
*	encountered a fatal error.
*	Returns the given exit code.
*/
int	kill_all_philos(t_rules *rules, int exit_code)
{
	unsigned int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		kill(rules->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

/* global_gluttony_reaper:
*	Kills all philosophers if each one has eaten enough. Each philosopher
*	process decrements the sem_philo_full semaphore. This thread registers
*	those decrementations to count how many philosophers have eaten enough.
*	If all philos have eaten enough, kills all philos to end simulation.
*/
void	*global_gluttony_reaper(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
	if (rules->must_eat_count < 0 || rules->time_to_die == 0
		|| rules->nb_philos == 1)
		return (NULL);
	sim_start_delay(rules->start_time);
	while (rules->philo_full_count < rules->nb_philos)
	{
		if (has_simulation_stopped(rules) == 1)
			return (NULL);
		sem_wait(rules->sem_philo_full);
		if (has_simulation_stopped(rules) == 0)
			rules->philo_full_count += 1;
		else
			return (NULL);
	}
	sem_wait(rules->sem_stop);
	rules->stop_sim = 1;
	kill_all_philos(rules, EXIT_SUCCESS);
	sem_post(rules->sem_philo_dead);
	sem_post(rules->sem_stop);
	return (NULL);
}

/* global_famine_reaper:
*	Kills all philosophers if one has died. Each philosopher
*	process decrements the sem_philo_dead semaphore upon philo death.
*	This thread registers the first decrementation and kills all philos
*	immediately.
*/
void	*global_famine_reaper(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
	if (rules->nb_philos == 1)
		return (NULL);
	sim_start_delay(rules->start_time);
	if (has_simulation_stopped(rules) == 1)
		return (NULL);
	sem_wait(rules->sem_philo_dead);
	if (has_simulation_stopped(rules) == 1)
		return (NULL);
	sem_wait(rules->sem_stop);
	rules->stop_sim = 1;
	kill_all_philos(rules, EXIT_SUCCESS);
	sem_post(rules->sem_philo_full);
	sem_post(rules->sem_stop);
	return (NULL);
}

/* end_condition_reached:
*	Checks this philosopher to see if one of two end conditions
*	has been reached. If the philosopher has died, decrements a semaphore
*	that will trigger "famine reaper" to kill all philos.
*	If the philosopher has eaten enough, decrements a semaphore that
*	will trigger "gluttony_reaper" to increase philo_full_count.
*	Returns 0 if the philosopher is alive.
*/
static int	end_condition_reached(t_rules *rules, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (get_time_in_ms() - philo->last_meal >= rules->time_to_die)
	{
		write_status(philo, 1, DIED);
		sem_post(rules->this_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (1);
	}
	if (rules->must_eat_count != -1 && philo->ate_enough == 0
		&& philo->times_ate >= (unsigned int)rules->must_eat_count)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = 1;
	}
	sem_post(philo->sem_meal);
	return (0);
}

/* personal_grim_reaper:
*	The grim reaper thread's routine. Checks if this philosopher must
*	be killed and if he ate enough.
*/
void	*personal_grim_reaper(void *data)
{
	t_rules			*rules;

	rules = (t_rules *)data;
	if (rules->must_eat_count == 0)
		return (NULL);
	sem_wait(rules->this_philo->sem_philo_dead);
	sem_wait(rules->this_philo->sem_philo_full);
	sim_start_delay(rules->start_time);
	while (!end_condition_reached(rules, rules->this_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
