/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:37:16 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	error_msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, "philo_bonus error :");
	else
		printf(str, "philo_bonus error :", detail);
	return (exit_no);
}

int	ft_error(char *str, char *details, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	return (error_msg(str, details, 0));
}

void	*error_null(char *str, char *details, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	error_msg(str, details, EXIT_FAILURE);
	return (NULL);
}

void	child_exit(t_rules *rules, int exit_code)
{
	sem_post(rules->this_philo->sem_meal);
	pthread_join(rules->this_philo->personal_grim_reaper, NULL);
	if (exit_code == CHILD_EXIT_ERR_SEM)
		error_msg("%sCould not create semaphore.\n", NULL, 0);
	if (exit_code == CHILD_EXIT_ERR_PTHREAD)
		error_msg("%sCould not create thread.\n", NULL, 0);
	sem_close(rules->this_philo->sem_forks);
	sem_close(rules->this_philo->sem_philo_full);
	sem_close(rules->this_philo->sem_philo_dead);
	sem_close(rules->this_philo->sem_write);
	sem_close(rules->this_philo->sem_meal);
	free_rules(rules);
	exit(exit_code);
}
