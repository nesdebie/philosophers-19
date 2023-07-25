/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:18:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/25 12:05:04 by nesdebie         ###   ########.fr       */
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

static int	is_only_digits(char *str)
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

int	is_valid(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!is_only_digits(av[i]))
			return (error_msg("Not only-digits input found.", EXIT_FAILURE));
		nb = philo_atoi(av[i]);
		if (i == 1 && (nb <= 0))
			return (error_msg("Invalid amount of philosophers", EXIT_FAILURE));
		if (i != 1 && (nb <= 0))
			return (error_msg("Invalid parameter", EXIT_FAILURE));
		if (i != 1 && nb == -1)
			return (error_msg("Too big input.", EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}
