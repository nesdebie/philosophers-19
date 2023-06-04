/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:16:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/04 14:16:56 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_rules	rules;
	int		ret;

	if (ac < 5)
		return (ft_error("Not enough arguments (min. 4)"));
	else if (ac > 6)
		return (ft_error("Too many arguments (max. 5)"));
	ret = init_manager(&rules, av);
	if (ret == WRONG_ARGS)
		return (ft_error("At least one wrong argument\nPlease try again !"));
	else if (ret == MUTEX_FAIL)
		return (ft_error("pthread_mutex_init() failed"));
	if (!launcher(&rules))
		return (ft_error("pthread_create() failed"));
	return (0);
}