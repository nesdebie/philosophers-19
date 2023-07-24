/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/24 14:48:45 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	error_msg(char *str, int exit_nb)
{
	printf("philo_bonus: error: %s\n", str);
	return (exit_nb);
}

int	ft_error(char *str, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	return (error_msg(str, EXIT_FAILURE));
}

void	*error_null(char *str, t_rules *rules)
{
	ft_error(str, rules);
	return (0);
}

void	child_exit(t_rules *rules, int exit_code)
{
	sem_post(rules->this_philo->sem_meal);
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
	free_rules(rules);
	exit(exit_code);
}

int	rules_cleanup(t_rules *rules, int exit_code)
{
	if (rules)
	{
		pthread_join(rules->dead, NULL);
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
