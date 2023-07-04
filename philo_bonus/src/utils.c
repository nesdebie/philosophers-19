/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:18:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/04 10:05:43 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char const *str)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return ((int)(sign * result));
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	better_usleep(long long time, t_rules *rules)
{
	long long	i;

	i = get_time();
	while (!(rules->dead))
	{
		if ((get_time() - i) >= time)
			break ;
		usleep(rules->nb_philo * 2);
	}
}

void	print_routine(t_rules *rules, int id, char *s)
{
	pthread_mutex_lock(&(rules->state_write));
	if (!(rules->dead))
		printf("%lli %i %s\n", get_time() - rules->first_timestamp, id + 1, s);
	pthread_mutex_unlock(&(rules->state_write));
}
