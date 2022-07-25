/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:20 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/25 12:13:57 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->number_of_philosophers;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (1);
	return (0);
}

static int	init_philosophers(t_rules *rules)
{
	int	i;

	i = rules->number_of_philosophers;
	while (--i >= 0)
	{
		rules->phi[i].id = i;
		rules->phi[i].x_ate = 0;
		rules->phi[i].left_fork_id = i;
		rules->phi[i].right_fork_id = (i + 1) % rules->number_of_philosophers;
		rules->phi[i].t_last_meal = 0;
		rules->phi[i].rules = rules;
	}
	return (0);
}

int	init_manager(t_rules *rules, char **argv)
{
	rules->number_of_philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->dead = 0;
	if (rules->number_of_philosophers < 2 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->number_of_philosophers > 250)
		return (1);
	if (argv[5])
	{
		rules->number_of_philo_meals = ft_atoi(argv[5]);
		if (rules->number_of_philo_meals <= 0)
			return (1);
	}
	else
		rules->number_of_philo_meals = -1;
	if (init_mutex(rules))
		return (2);
	init_philosophers(rules);
	return (0);
}
