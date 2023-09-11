/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/11 15:59:39 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_rules(t_rules *rules, int error, int end)
{
	int	i;

	if (end == -1)
		if (error == WRONG_ARGS)
			return (1);
	if (!error)
		end = rules->nb_philo;
	if (rules->forks != NULL)
	{
		i = 0;
		while (i < end)
			pthread_mutex_destroy(&rules->forks[i++]);
		free(rules->forks);
	}
	if (rules->phi != NULL)
		free(rules->phi);
	pthread_mutex_destroy(&rules->state_write);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	rules;
	int		ret;

	ret = 0;
	if (ac < 5 || ac > 6)
		return (ft_error("Wrong amount of arguments (min. 5 to 6)", 0));
	ret = init_manager(&rules, av);
	if (ret)
	{
		free_rules(&rules, ret, -1);
		return (ft_error(NULL, ret));
	}
	ret = philo_threads(&rules);
	if (ret)
	{
		free_rules(&rules, 0, ret);
		return (ft_error("pthread_create() failed", 0));
	}
	free_rules(&rules, 0, -1);
	return (EXIT_SUCCESS);
}
