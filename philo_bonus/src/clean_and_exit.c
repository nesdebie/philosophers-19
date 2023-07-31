/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:36:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/31 12:27:35 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	unlink_global_sems(void)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("fed");
	sem_unlink("dead");
	sem_unlink("stop");
}

void	*free_rules(t_rules *rules)
{
	unsigned int	i;

	if (!rules)
		return (0);
	if (rules->philos)
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			if (rules->philos[i])
				free(rules->philos[i]);
			i++;
		}
		free(rules->philos);
	}
	if (rules->pids)
		free(rules->pids);
	free(rules);
	return (0);
}

void	child_exit(t_rules *rules, int exit_code)
{
	sem_post(rules->this_philo->sem_meal);
	if (rules->this_philo->p_killer)
		pthread_join(rules->this_philo->p_killer, NULL);
	if (exit_code == ERR_SEM)
		error_msg("Could not create semaphore.", EXIT_FAILURE);
	if (exit_code == ERR_PTHREAD)
		error_msg("Could not create thread.", EXIT_FAILURE);
	sem_close(rules->this_philo->sem_forks);
	sem_close(rules->this_philo->sem_philo_full);
	sem_close(rules->this_philo->sem_philo_dead);
	sem_close(rules->this_philo->sem_write);
	sem_close(rules->this_philo->sem_meal);
	if (exit_code == ERR_PTHREAD)
		unlink_global_sems();
	free_rules(rules);
	exit(exit_code);
}

int	rules_cleanup(t_rules *rules, int exit_code)
{
	if (rules)
	{
		if (rules->dead)
			pthread_join(rules->dead, NULL);
		if (rules->fed)
			pthread_join(rules->fed, NULL);
		sem_close(rules->sem_forks);
		sem_close(rules->sem_write);
		sem_close(rules->sem_philo_full);
		sem_close(rules->sem_philo_dead);
		sem_close(rules->sem_stop);
		unlink_global_sems();
		free_rules(rules);
	}
	exit (exit_code);
}
