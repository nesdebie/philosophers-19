/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:54 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:37:38 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
