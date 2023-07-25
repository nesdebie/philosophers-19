/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/25 12:02:57 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_action(t_philo *philo, int end_flag, int status)
{
	sem_wait(philo->sem_write);
	if (status == DIED)
		printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id + 1, "died");
	else if (status == EATING)
		printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id + 1, "is eating");
	else if (status == SLEEPING)
		printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id + 1, "is sleeping");
	else if (status == THINKING)
		printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id + 1, "is thinking");
	else if (status == FORK_1 || status == FORK_2)
		printf("%ld %d %s\n", get_time_in_ms() - philo->rules->start_time,
			philo->id + 1, "has taken a fork");
	if (!end_flag)
		sem_post(philo->sem_write);
}
