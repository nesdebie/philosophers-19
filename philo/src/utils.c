/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:18:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/19 12:52:59 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
		if (nb > OVERFLOW)
			return (-1);
	}
	return ((int)nb);
}

time_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	better_usleep(time_t sleep_time, t_rules *rules)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (!(rules->dead))
	{
		if (get_time() >= wake_up)
			break ;
		usleep(10);
	}
}

void	print_routine(t_rules *rules, int id, char *s)
{
	pthread_mutex_lock(&(rules->state_write));
	if (!(rules->dead))
		printf("%li %i %s\n", get_time() - rules->start_time, id + 1, s);
	pthread_mutex_unlock(&(rules->state_write));
}
