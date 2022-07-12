/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:20:21 by nedebies          #+#    #+#             */
/*   Updated: 2022/07/12 12:08:26 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int argc, char *argv[])
{
	t_rules	rules;
	int		ret;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong amount of arguments"));
	ret = init_all(&rules, argv);
	if (ret == 1)
		return (ft_error("At least one wrong argument"));
	else if (ret == 2)
		return (ft_error("Mutex initialization failed"));
	if (launcher(&rules))
		return (ft_error("There was an error creating the threads"));
	return (0);
}