/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 11:25:44 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	int		ret;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong amount of arguments (min. 5 to 6)\n"));
	ret = init_manager(&rules, av);
	if (ret == WRONG_ARGS)
		return (ft_error("At least one wrong argument\nPlease try again !\n"));
	else if (ret == MUTEX_FAIL)
		return (ft_error("pthread_mutex_init() failed\n"));
	else if (ret == MALLOC_FAIL)
		return (ft_error("malloc() failed\n"));
	if (!ft_create_threads(&rules))
	{
		free (rules.forks);
		free (rules.phi);
		return (ft_error("%spthread_create() failed\n"));
	}
	return (0);
}
