/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:20 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/28 15:29:21 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (0);
	}
	if (pthread_mutex_init(&(rules->state_write), NULL))
		return (0);
	return (1);
}

static int	init_philosophers(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->phi[i].id = i;
		rules->phi[i].is_fed = 0;
		rules->phi[i].left_fork_id = i;
		rules->phi[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->phi[i].t_last_meal = 0;
		rules->phi[i].rules = rules;
	}
	return (0);
}

int	init_manager(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->all_fed = 0;
	rules->dead = 0;
	if (rules->nb_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->nb_philo > 250)
		return (1);
	if (argv[5])
	{
		rules->nb_meals = ft_atoi(argv[5]);
		if (rules->nb_meals <= 0)
			return (1);
	}
	else
		rules->nb_meals = -1;
	if (!init_mutex(rules))
		return (2);
	init_philosophers(rules);
	return (0);
}
