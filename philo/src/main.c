/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/19 11:55:10 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	int		ret;
	int		i;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong amount of arguments (min. 5 to 6)"));
	ret = init_manager(&rules, av);
	if (ret == WRONG_ARGS)
		return (ft_error("At least one wrong argument."));
	else if (ret == MUTEX_FAIL)
		return (ft_error("pthread_mutex_init() failed"));
	else if (ret == MALLOC_FAIL)
		return (ft_error("malloc() failed"));
	if (philo_threads(&rules))
	{
		i = -1;
		while (++i < rules.nb_philo)
			pthread_mutex_destroy(&(rules.forks[i]));
		pthread_mutex_destroy(&(rules.state_write));
		free(rules.forks);
		free(rules.phi);
		return (ft_error("pthread_create() failed"));
	}
	return (EXIT_SUCCESS);
}
