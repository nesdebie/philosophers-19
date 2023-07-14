/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 11:31:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static char	*set_local_sem_name(const char *str, unsigned int id)
{
	unsigned int	i;
	unsigned int	digit_count;
	char			*sem_name;
	char			*tmp;

	digit_count = 0;
	i = id;
	while (i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc (sizeof * sem_name * (i + 1));
	if (sem_name == NULL)
		return (0);
	sem_name[0] = 0;
	sem_name = ft_strcat(sem_name, str);
	tmp = ft_utoa(id, digit_count);
	sem_name = ft_strcat(sem_name, tmp);
	free(tmp);
	return (sem_name);
}

static int	set_philo_sem_names(t_philo *philo)
{
	philo->sem_meal_name = set_local_sem_name("meal_", philo->id + 1);
	if (philo->sem_meal_name == NULL)
		return (0);
	return (1);
}

static t_philo	**init_philosophers(t_rules *rules)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * (rules->nb_philos + 1));
	if (!philos)
		return (error_null("Could not allocate memory.\n", 0));
	i = 0;
	while (i < rules->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_null("Could not allocate memory.\n", 0));
		philos[i]->rules = rules;
		philos[i]->id = i;
		if (!set_philo_sem_names(philos[i]))
			return (error_null("Could not allocate memory.\n", rules));
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
	if (rules->sem_forks == SEM_FAILED)
		return (sem_error_cleanup(rules));
	rules->sem_write = sem_open("write", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (rules->sem_write == SEM_FAILED)
		return (sem_error_cleanup(rules));
	rules->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, rules->nb_philos);
	if (rules->sem_philo_full == SEM_FAILED)
		return (sem_error_cleanup(rules));
	rules->sem_philo_dead = sem_open("dead", O_CREAT,
			S_IRUSR | S_IWUSR, rules->nb_philos);
	if (rules->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleanup(rules));
	rules->sem_stop = sem_open("stop", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (rules->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(rules));
	return (1);
}

t_rules	*init_rules(int ac, char **av, int i)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules) * 1);
	if (!rules)
		return (error_null("Could not allocate memory.\n", 0));
	rules->nb_philos = integer_atoi(av[i++]);
	rules->time_to_die = integer_atoi(av[i++]);
	rules->time_to_eat = integer_atoi(av[i++]);
	rules->time_to_sleep = integer_atoi(av[i++]);
	rules->must_eat_count = -1;
	rules->philo_full_count = 0;
	rules->stop_sim = 0;
	if (ac - 1 == 5)
		rules->must_eat_count = integer_atoi(av[i]);
	if (!init_global_semaphores(rules))
		return (0);
	rules->philos = init_philosophers(rules);
	if (!rules->philos)
		return (0);
	rules->pids = malloc(sizeof * rules->pids * rules->nb_philos);
	if (!rules->pids)
		return (error_null("Could not allocate memory.\n", 0));
	return (rules);
}
