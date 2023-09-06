/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 14:13:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

static t_philo	**init_philosophers(t_rules *rules)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * (rules->nb_philos + 1));
	if (!philos)
		return (error_null("Could not allocate memory.", 0));
	i = 0;
	while (i < rules->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_null("Could not allocate memory.", rules));
		philos[i]->rules = rules;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		philos[i]->nb_forks_held = 0;
		philos[i]->ate_enough = 0;
		i++;
	}
	return (philos);
}

static int	init_global_semaphores(t_rules *rules)
{
	unlink_global_sems();
	rules->sem_forks = sem_open("forks", O_CREAT,
			S_IRUSR | S_IWUSR, rules->nb_philos);
	if (rules->sem_forks == (sem_t *)-1)
		return (sem_error_cleanup(rules));
	rules->sem_write = sem_open("write", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (rules->sem_write == (sem_t *)-1)
		return (sem_error_cleanup(rules));
	rules->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, rules->nb_philos);
	if (rules->sem_philo_full == (sem_t *)-1)
		return (sem_error_cleanup(rules));
	rules->sem_philo_dead = sem_open("dead", O_CREAT,
			S_IRUSR | S_IWUSR, rules->nb_philos);
	if (rules->sem_philo_dead == (sem_t *)-1)
		return (sem_error_cleanup(rules));
	rules->sem_stop = sem_open("stop", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (rules->sem_stop == (sem_t *)-1)
		return (sem_error_cleanup(rules));
	return (EXIT_SUCCESS);
}

t_rules	*init_rules(int ac, char **av)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (error_null("Could not allocate memory.", 0));
	rules->nb_philos = philo_atoi(av[1]);
	rules->time_to_die = philo_atoi(av[2]);
	rules->time_to_eat = philo_atoi(av[3]);
	rules->time_to_sleep = philo_atoi(av[4]);
	rules->must_eat_count = -1;
	rules->philo_full_count = 0;
	rules->stop = 0;
	if (ac - 1 == 5)
		rules->must_eat_count = philo_atoi(av[5]);
	if (init_global_semaphores(rules))
		return (NULL);
	rules->philos = init_philosophers(rules);
	if (!rules->philos)
		return (NULL);
	rules->pids = malloc(sizeof * rules->pids * rules->nb_philos);
	if (!rules->pids)
		return (error_null("Could not allocate memory.", rules));
	return (rules);
}
