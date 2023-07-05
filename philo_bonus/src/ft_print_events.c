/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:11:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* print_status:
*	Prints a philosopher's status in plain text as required by the project
*	subject:
*		timestamp_in_ms X status
*/
void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
		philo->id + 1, str);
}

/* write_status:
*	Prints the status of a philosopher. Decrements the write semaphore to
*	avoid intertwined messages from different processes. If the message comes
*	from a grim reaper, the write semaphore is not increased again after
*	the message is displayed in the terminal, to avoid any status messages
*	being displayed after a philosopher has died.
*/
void	write_status(t_philo *philo, int reaper_report, t_status status)
{
	sem_wait(philo->sem_write);
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	if (!reaper_report)
		sem_post(philo->sem_write);
}

/* write_outcome:
*	Prints the outcome of the simulation if a number of times to
*	eat was specified. Only used for debug purposes.
*/
void	write_outcome(t_rules *rules)
{
	sem_post(rules->sem_write);
	sem_wait(rules->sem_write);
	printf("%d/%d philosophers had at least %d meals.\n",
		rules->philo_full_count, rules->nb_philos, rules->must_eat_count);
	sem_post(rules->sem_write);
	return ;
}

