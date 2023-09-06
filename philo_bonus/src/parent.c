/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:20:06 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 11:57:48 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	get_child_philo(t_rules *rules, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG))
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == DIED)
				return (kill_all_philos(rules, 1));
			if (exit_code == ERR_PTHREAD || exit_code == ERR_SEM)
				return (kill_all_philos(rules, -1));
			if (exit_code == FULL)
			{
				rules->philo_full_count += 1;
				return (1);
			}
		}
	}
	return (0);
}

int	philo_stop(t_rules	*rules)
{
	unsigned int	i;
	int				exit_code;

	sim_start_delay(rules->start_time);
	while (!is_stopped(rules))
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			exit_code = get_child_philo(rules, &rules->pids[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(rules->sem_stop);
				rules->stop = 1;
				sem_post(rules->sem_philo_full);
				sem_post(rules->sem_philo_dead);
				sem_post(rules->sem_stop);
				return (exit_code);
			}
			i++;
		}
	}
	return (0);
}
