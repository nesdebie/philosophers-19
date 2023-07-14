/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 14:07:43 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	rules_cleanup(t_rules *rules, int exit_code)
{
	if (rules)
	{
		pthread_join(rules->starved, NULL);
		pthread_join(rules->fed, NULL);
		sem_close(rules->sem_forks);
		sem_close(rules->sem_write);
		sem_close(rules->sem_philo_full);
		sem_close(rules->sem_philo_dead);
		sem_close(rules->sem_stop);
		unlink_global_sems();
		free_rules(rules);
	}
	return (exit_code);
}

static int	start_simulation(t_rules *rules)
{
	unsigned int	i;
	pid_t			pid;

	rules->start_time = get_time_in_ms() + ((rules->nb_philos * 2) * 10);
	i = -1;
	while (++i < rules->nb_philos)
	{
		pid = fork();
		if (pid == -1)
			return (ft_error("Could not fork child.\n", rules));
		else if (pid > 0)
			rules->pids[i] = pid;
		else if (pid == 0)
		{
			rules->this_philo = rules->philos[i];
			philosopher(rules);
		}
	}
	if (!set_death_threads(rules))
		return (0);
	return (1);
}

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

static int	stop_simulation(t_rules	*rules)
{
	unsigned int	i;
	int				exit_code;

	sim_start_delay(rules->start_time);
	while (!has_simulation_stopped(rules))
	{
		i = 0;
		while (i < rules->nb_philos)
		{
			exit_code = get_child_philo(rules, &rules->pids[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(rules->sem_stop);
				rules->stop_sim = 1;
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

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg("Wrong amount of arguments.", EXIT_FAILURE));
	if (!is_valid(ac, av))
		return (EXIT_FAILURE);
	rules = init_rules(ac, av);
	if (!rules)
		return (EXIT_FAILURE);
	if (!start_simulation(rules))
		return (EXIT_FAILURE);
	if (stop_simulation(rules) == -1)
		return (rules_cleanup(rules, EXIT_FAILURE));
	return (rules_cleanup(rules, EXIT_SUCCESS));
}
