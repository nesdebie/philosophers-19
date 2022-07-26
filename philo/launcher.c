/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:41:15 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/26 14:29:09 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	print_routine(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	print_routine(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	print_routine(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	(philo->x_ate)++;
	philo_sleep(rules->time_to_eat, rules);
	pthread_mutex_unlock(&(rules->meal_check));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

static void	*routine(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dead))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		print_routine(rules, philo->id, "is sleeping");
		philo_sleep(rules->time_to_sleep, rules);
		print_routine(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

static void	ft_destroyer(t_rules *r)
{
	int	i;

	if (r->number_of_philosophers > 1)
	{
		i = -1;
		while (++i < r->number_of_philosophers)
			pthread_join(r->phi[i].thread_id, NULL);
	}
	i = -1;
	while (++i < r->number_of_philosophers)
		pthread_mutex_destroy(&(r->forks[i]));
	pthread_mutex_destroy(&(r->writing));
}

static void	is_dead(t_rules *r)
{
	int	i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->number_of_philosophers && !(r->dead))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (timestamp() - r->phi[i].t_last_meal > r->time_to_die)
			{
				print_routine(r, i, "died");
				r->dead = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dead)
			break ;
		i = 0;
		while (r->number_of_philo_meals != -1 && i < r->number_of_philosophers
			&& r->phi[i].x_ate >= r->number_of_philo_meals)
			i++;
		if (i == r->number_of_philosophers)
			r->all_ate = 1;
	}
}

int	launcher(t_rules *r)
{
	int				i;

	i = 0;
	r->first_timestamp = timestamp();
	while (i < r->number_of_philosophers)
	{
		if (pthread_create(&(r->phi[i].thread_id), NULL, routine, &(r->phi[i])))
			return (0);
		r->phi[i].t_last_meal = timestamp();
		i++;
	}
	is_dead(r);
	ft_destroyer(r);
	return (1);
}
