/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 14:59:00 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

time_t	get_time(void)
{
	struct timeval		tval;

	gettimeofday(&tval, NULL);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

void	philo_sleep(time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		usleep(100);
	}
}

void	sim_start_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}
