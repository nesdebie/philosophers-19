/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:45:34 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 10:32:44 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	grab_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->nb_forks_held <= 0)
		write_status(philo, 0, GOT_FORK_1);
	if (philo->nb_forks_held == 1)
		write_status(philo, 0, GOT_FORK_2);
	philo->nb_forks_held += 1;
	sem_post(philo->sem_meal);
}

void	*free_rules(t_rules *rules)
{
	unsigned int	i;

	if (!rules)
		return (NULL);
	if (rules->philos)
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			if (rules->philos[i])
			{
				if (rules->philos[i]->sem_meal_name)
					free(rules->philos[i]->sem_meal_name);
				free(rules->philos[i]);
			}
			i++;
		}
		free(rules->philos);
	}
	if (rules->pids)
		free(rules->pids);
	free(rules);
	return (NULL);
}

int	sem_error_cleanup(t_rules *rules)
{
	sem_close(rules->sem_forks);
	sem_close(rules->sem_write);
	sem_close(rules->sem_philo_full);
	sem_close(rules->sem_philo_dead);
	sem_close(rules->sem_stop);
	unlink_global_sems();
	return (ft_error("%sCould not create semaphore.\n", NULL, rules));
}

int	rules_cleanup(t_rules *rules, int exit_code)
{
	if (rules)
	{
		pthread_join(rules->famine_reaper, NULL);
		pthread_join(rules->gluttony_reaper, NULL);
		sem_close(rules->sem_forks);
		sem_close(rules->sem_write);
		sem_close(rules->sem_philo_full);
		sem_close(rules->sem_philo_dead);
		sem_close(rules->sem_stop);
		unlink_global_sems();
		free_rules(rules);
	}
	return (exit_code);
}
