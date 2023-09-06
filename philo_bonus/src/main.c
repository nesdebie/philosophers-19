/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/06 11:58:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	set_threads(t_rules *rules)
{
	if (pthread_create(&rules->fed, NULL, &ft_all_fed, rules))
		return (ft_error("Could not create thread.", rules));
	if (pthread_create(&rules->dead, NULL, &ft_starve_to_death, rules))
		return (ft_error("Could not create thread.", rules));
	return (EXIT_SUCCESS);
}

static int	philo_start(t_rules *rules)
{
	unsigned int	i;
	pid_t			pid;

	rules->start_time = get_time_in_ms() + ((rules->nb_philos * 2) * 10);
	i = -1;
	while (++i < rules->nb_philos)
	{
		pid = fork();
		if (pid == -1)
			return (ft_error("Could not fork child.", rules));
		else if (pid > 0)
			rules->pids[i] = pid;
		else if (!pid)
		{
			rules->this_philo = rules->philos[i];
			philosopher(rules);
		}
	}
	if (set_threads(rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg("Wrong amount of arguments.", EXIT_FAILURE));
	if (is_valid(ac, av))
		exit(EXIT_FAILURE);
	rules = init_rules(ac, av);
	if (!rules)
		exit(EXIT_FAILURE);
	if (philo_start(rules))
		exit(EXIT_FAILURE);
	if (philo_stop(rules) == -1)
		return (rules_cleanup(rules, EXIT_FAILURE));
	return (rules_cleanup(rules, EXIT_SUCCESS));
}
