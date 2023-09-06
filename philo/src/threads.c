/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:17:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 14:35:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_destroyer(t_rules *r)
{
	int	i;

	if (r->nb_philo > 1)
	{
		i = -1;
		while (++i < r->nb_philo)
			pthread_join(r->phi[i].thread_id, NULL);
	}
	i = -1;
	while (++i < r->nb_philo)
		pthread_mutex_destroy(&(r->forks[i]));
	free(r->forks);
	free(r->phi);
	pthread_mutex_destroy(&(r->state_write));
}

static void	is_dead(t_rules *r)
{
	int	i;

	while (!(r->all_fed))
	{
		i = -1;
		while (++i < r->nb_philo)
		{
			if (get_time() - r->phi[i].t_last_meal > r->time_to_die)
			{
				print_routine(r, i, "died");
				r->dead = 1;
				break ;
			}
			usleep(100);
		}
		if (r->dead)
			break ;
		i = 0;
		while (r->nb_meals != -1 && i < r->nb_philo
			&& r->phi[i].is_fed >= r->nb_meals)
			i++;
		if (i == r->nb_philo)
			r->all_fed = 1;
	}
}

static void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	print_routine(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	print_routine(rules, philo->id, "has taken a fork");
	print_routine(rules, philo->id, "is eating");
	philo->t_last_meal = get_time();
	(philo->is_fed)++;
	better_usleep(rules->time_to_eat, rules);
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

static void	*routine(void *void_philosopher)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dead))
	{
		philo_eats(philo);
		if (rules->all_fed)
			break ;
		print_routine(rules, philo->id, "is sleeping");
		better_usleep(rules->time_to_sleep, rules);
		print_routine(rules, philo->id, "is thinking");
	}
	return (0);
}

int	ft_create_threads(t_rules *r)
{
	int				i;

	i = 0;
	r->first_timestamp = get_time();
	while (i < r->nb_philo)
	{
		if (pthread_create(&(r->phi[i].thread_id), NULL, routine, &(r->phi[i])))
			return (EXIT_FAILURE);
		r->phi[i].t_last_meal = get_time();
		i++;
	}
	is_dead(r);
	ft_destroyer(r);
	return (EXIT_SUCCESS);
}
