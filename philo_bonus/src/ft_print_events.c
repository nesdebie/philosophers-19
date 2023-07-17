/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/17 12:14:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_action(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
		philo->id + 1, str);
}

void	print_action_parser(t_philo *philo, int reaper_report, int status)
{
	sem_wait(philo->sem_write);
	if (status == DIED)
		print_action(philo, "died");
	else if (status == EATING)
		print_action(philo, "is eating");
	else if (status == SLEEPING)
		print_action(philo, "is sleeping");
	else if (status == THINKING)
		print_action(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_action(philo, "has taken a fork");
	if (!reaper_report)
		sem_post(philo->sem_write);
}
