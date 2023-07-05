/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:45:34 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:23:36 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* grab_fork:
*	Wait for the fork semaphore to allow the philosopher to take a
*	fork. When the philosopher takes a fork, the semaphore is decreased
*	by 1 to represent the fact that there is one less fork available
*	in the pool of forks.
*	There is no real distinction between the first and second fork a
*	philosopher takes, the dictinction is made here only for debut purposes.
*/
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

/* free_rules:
*	Frees all of the memory allocated by the program.
*	Returns a NULL pointer if there is nothing to free,
*	or when all memory has been freed.
*/
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

/* sem_error_cleanup:
*	Closes and unlinks all semaphores. Used only during
*	initialization, in case a semaphore fails to be opened.
*	Returns 0 for failure.
*/
int	sem_error_cleanup(t_rules *rules)
{
	sem_close(rules->sem_forks);
	sem_close(rules->sem_write);
	sem_close(rules->sem_philo_full);
	sem_close(rules->sem_philo_dead);
	sem_close(rules->sem_stop);
	unlink_global_sems();
	return (error_failure("%s error: Could not create semaphore.\n", NULL, rules));
}

/* rules_cleanup:
*	Closes all semaphores and frees any allocated memory.
*	Also waits for the global grim reaper thread to terminate.
*	Returns the provided exit code.
*/
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