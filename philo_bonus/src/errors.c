/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 11:38:58 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	detailed_error_msg(char *str, char *status, int exit_no)
{
	printf("philo_bonus error :");
	printf(str, status);
	return (exit_no);
}

int	error_msg(char *str, int exit_no)
{
	printf("philo_bonus error :");
	printf("%s", str);
	return (exit_no);
}

int	ft_error(char *str, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	return (error_msg(str, 0));
}

void	*error_null(char *str, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	error_msg(str, EXIT_FAILURE);
	return (0);
}

void	child_exit(t_rules *rules, int exit_code)
{
	sem_post(rules->this_philo->sem_meal);
	pthread_join(rules->this_philo->personal_grim_reaper, NULL);
	if (exit_code == ERR_SEM)
		error_msg("Could not create semaphore.\n", 0);
	if (exit_code == ERR_PTHREAD)
		error_msg("Could not create thread.\n", 0);
	sem_close(rules->this_philo->sem_forks);
	sem_close(rules->this_philo->sem_philo_full);
	sem_close(rules->this_philo->sem_philo_dead);
	sem_close(rules->this_philo->sem_write);
	sem_close(rules->this_philo->sem_meal);
	free_rules(rules);
	exit(exit_code);
}
