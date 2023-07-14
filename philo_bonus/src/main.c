/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 11:33:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	has_simulation_stopped(t_rules *rules)
{
	int	ret;

	sem_wait(rules->sem_stop);
	ret = rules->stop_sim;
	sem_post(rules->sem_stop);
	return (ret);
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
	if (set_death_threads(rules) == 0)
		return (0);
	return (1);
}

static int	get_child_philo(t_rules *rules, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == DIED)
				return (kill_all_philos(rules, 1));
			if (exit_code == ERR_PTHREAD
				|| exit_code == ERR_SEM)
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
	while (has_simulation_stopped(rules) == 0)
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
		return (error_msg("Wrong amount of arguments (min. 5 to 6)", EXIT_FAILURE));
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	rules = init_rules(ac, av, 1);
	if (!rules)
		return (EXIT_FAILURE);
	if (!start_simulation(rules))
		return (EXIT_FAILURE);
	if (stop_simulation(rules) == -1)
		return (rules_cleanup(rules, EXIT_FAILURE));
	return (rules_cleanup(rules, EXIT_SUCCESS));
}
