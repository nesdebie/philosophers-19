/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:08 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 10:44:44 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	philo_open_global_semaphores(t_philo *philo)
{
	philo->sem_forks = sem_open("forks", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_forks == SEM_FAILED)
		return (0);
	philo->sem_write = sem_open("write", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (0);
	philo->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		return (0);
	philo->sem_philo_dead = sem_open("dead", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_dead == SEM_FAILED)
		return (0);
	return (1);
}

static int	philo_open_local_semaphores(t_philo *philo)
{
	philo->sem_meal = sem_open(philo->sem_meal_name, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_meal == SEM_FAILED)
		return (0);
	sem_unlink(philo->sem_meal_name);
	return (1);
}

void	init_philo_ipc(t_rules *rules, t_philo *philo)
{
	if (rules->nb_philos == 1)
		return ;
	sem_unlink(philo->sem_meal_name);
	if (!philo_open_global_semaphores(philo))
		child_exit(rules, ERR_SEM);
	if (!philo_open_local_semaphores(philo))
		child_exit(rules, ERR_SEM);
	if (pthread_create(&philo->personal_grim_reaper, NULL,
			&personal_grim_reaper, rules) != 0)
		child_exit(rules, ERR_PTHREAD);
	return ;
}
