/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:15:42 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/04 10:05:17 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (EXIT_FAILURE);
}
