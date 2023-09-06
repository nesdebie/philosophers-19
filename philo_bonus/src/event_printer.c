/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 14:59:00 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_action(t_philo *philo, int end_flag, int status)
{
	char	*arr[6];

	arr[DIED] = "died";
	arr[EATING] = "is eating";
	arr[SLEEPING] = "is sleeping";
	arr[THINKING] = "is thinking";
	arr[FORK_1] = "has taken a fork";
	arr[FORK_2] = arr[FORK_1];
	sem_wait(philo->sem_write);
	printf("%ld %d %s\n", get_time() - philo->rules->start_time,
		philo->id + 1, arr[status]);
	if (!end_flag)
		sem_post(philo->sem_write);
}
