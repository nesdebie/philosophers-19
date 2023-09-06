/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:18:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 14:19:39 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
