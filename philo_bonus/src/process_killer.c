/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_killer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:54 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 11:58:11 by nesdebie         ###   ########.fr       */
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

void	*ft_all_fed(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
	if (rules->nb_philos == 1)
		return (0);
	if (rules->must_eat_count < 0 || !rules->time_to_die)
		return (0);
	sim_start_delay(rules->start_time);
	while (rules->philo_full_count < rules->nb_philos)
	{
		if (is_stopped(rules))
			return (0);
		sem_wait(rules->sem_philo_full);
		if (!is_stopped(rules))
			rules->philo_full_count += 1;
		else
			return (0);
	}
	sem_wait(rules->sem_stop);
	rules->stop = 1;
	kill_all_philos(rules, EXIT_SUCCESS);
	sem_post(rules->sem_philo_dead);
	sem_post(rules->sem_stop);
	return (0);
}

void	*ft_starve_to_death(void *data)
{
	t_rules	*rules;

	rules = (t_rules *)data;
	if (rules->nb_philos == 1)
		return (0);
	sim_start_delay(rules->start_time);
	if (is_stopped(rules))
		return (0);
	sem_wait(rules->sem_philo_dead);
	if (is_stopped(rules))
		return (0);
	sem_wait(rules->sem_stop);
	rules->stop = 1;
	kill_all_philos(rules, EXIT_SUCCESS);
	sem_post(rules->sem_philo_full);
	sem_post(rules->sem_stop);
	return (0);
}
