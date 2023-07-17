/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:43:13 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 15:24:43 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	is_stopped(t_rules *rules)
{
	int	ret;

	sem_wait(rules->sem_stop);
	ret = rules->stop;
	sem_post(rules->sem_stop);
	return (ret);
}

static int	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
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
	}
	if (nb > INT32_MAX)
		return (-1);
	return ((int)nb);
}

int	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!only_digits(av[i]))
			return (error_msg("Not only-digits input found.\n", EXIT_FAILURE));
		nb = philo_atoi(av[i]);
		if (i == 1 && (nb <= 0))
			return (error_msg("Too many philosophers", EXIT_FAILURE));
		if (i != 1 && nb == -1)
			return (error_msg("Too big input.\n", EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}