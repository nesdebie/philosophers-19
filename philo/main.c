/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:20:21 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/25 12:31:14 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_rules	rules;
	int		ret;

	if (argc < 5)
		return (ft_error("Not enough arguments (min. 4)"));
	else if (argc > 6)
		return (ft_error("Too many arguments (max. 5)"));
	ret = init_manager(&rules, argv);
	if (ret == 1)
		return (ft_error("At least one wrong argument\nPlease try again !"));
	else if (ret == 2)
		return (ft_error("pthread_mutex_init() failed"));
	if (!launcher(&rules))
		return (ft_error("pthread_create() failed"));
	return (0);
}
