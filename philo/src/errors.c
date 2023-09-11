/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/09/11 15:48:29 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *str, int error)
{
	if (!error)
		printf("philo error: %s\n", str);
	else if (error == WRONG_ARGS)
		printf("philo error: Incorrect ARUMENT\n");
	else
		printf("philo error: Malloc failed\n");
	return (EXIT_FAILURE);
}
