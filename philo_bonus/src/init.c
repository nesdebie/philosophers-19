/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/04 10:05:32 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	init_mutex(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(*(rules->forks)) * rules->nb_philo);
	if (!rules->forks)
		return (0);
	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
		{
			free (rules->forks);
			return (0);
		}
	}
	if (pthread_mutex_init(&(rules->state_write), NULL))
	{
		free (rules->forks);
		return (0);
	}
	return (1);
}

static void	init_philosophers(t_rules *rules)
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
}

static int	rules_checker(t_rules *rules, char *fifth_arg)
{
	if (rules->nb_philo < 1 || rules->time_to_die < 0)
		return (WRONG_ARGS);
	if (rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (WRONG_ARGS);
	if (fifth_arg && rules->nb_meals <= 0)
		return (WRONG_ARGS);
	return (0);
}

int	init_manager(t_rules *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	rules->all_fed = 0;
	rules->dead = 0;
	if (av[5])
		rules->nb_meals = ft_atoi(av[5]);
	else
		rules->nb_meals = -1;
	if (rules_checker(rules, av[5]))
		return (WRONG_ARGS);//DIFF
	if (!init_mutex(rules))
		return (MUTEX_FAIL);
	rules->phi = malloc(sizeof(rules->phi) * rules->nb_philo);
	if (!rules->phi)
	{
		free(rules->forks);
		return (MALLOC_FAIL);
	}
	init_philosophers(rules);
	return (0);
}
