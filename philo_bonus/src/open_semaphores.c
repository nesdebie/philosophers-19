/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:47:08 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/25 14:04:47 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	open_semaphores2(t_philo *philo)
{
	philo->sem_forks = sem_open("forks", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_forks == (sem_t *)-1)
		return (0);
	philo->sem_write = sem_open("write", O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == (sem_t *)-1)
		return (0);
	philo->sem_philo_full = sem_open("fed", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_full == (sem_t *)-1)
		return (0);
	philo->sem_philo_dead = sem_open("dead", O_CREAT,
			S_IRUSR | S_IWUSR, philo->rules->nb_philos);
	if (philo->sem_philo_dead == (sem_t *)-1)
		return (0);
	return (1);
}

void	open_semaphores(t_rules *rules, t_philo *philo)
{
	if (rules->nb_philos == 1)
		return ;
	if (!open_semaphores2(philo))
		child_exit(rules, ERR_SEM);
	if (pthread_create(&philo->p_killer, NULL, &process_killer, rules))
		child_exit(rules, ERR_PTHREAD);
}
