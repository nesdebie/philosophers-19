/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:24:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* error_msg:
*	Writes a message to the console. Returns the provided exit number.
*	Used for error management.
*/
int	error_msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, "philo_bonus");
	else
		printf(str, "philo_bonus", detail);
	return (exit_no);
}

/* error_failure:
*	Frees any allocated memory, prints an error message and
*	returns 0 to indicate failure.
*	Used for error management during initialization.
*/
int	error_failure(char *str, char *details, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	return (error_msg(str, details, 0));
}

/* error_null:
*	Frees any allocated memory, prints an error message and returns a NULL pointer.
*	Used for error management during initialization.
*/
void	*error_null(char *str, char *details, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	error_msg(str, details, EXIT_FAILURE);
	return (NULL);
}

/* child_exit:
*	Exits a child philosopher process with the appropriate exit code.
*	Prints an error message if the child encountered an error.
*/
void	child_exit(t_rules *rules, int exit_code)
{
	sem_post(rules->this_philo->sem_meal);
	pthread_join(rules->this_philo->personal_grim_reaper, NULL);
	if (exit_code == CHILD_EXIT_ERR_SEM)
		error_msg("%s error: Could not create semaphore.\n", NULL, 0);
	if (exit_code == CHILD_EXIT_ERR_PTHREAD)
		error_msg("%s error: Could not create thread.\n", NULL, 0);
	sem_close(rules->this_philo->sem_forks);
	sem_close(rules->this_philo->sem_philo_full);
	sem_close(rules->this_philo->sem_philo_dead);
	sem_close(rules->this_philo->sem_write);
	sem_close(rules->this_philo->sem_meal);
	free_rules(rules);
	exit(exit_code);
}
