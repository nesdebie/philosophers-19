/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:44:00 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/25 12:12:27 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	error_msg(char *str, int exit_nb)
{
	printf("philo_bonus: error: %s\n", str);
	return (exit_nb);
}

int	ft_error(char *str, t_rules *rules)
{
	if (rules)
		free_rules(rules);
	return (error_msg(str, EXIT_FAILURE));
}

void	*error_null(char *str, t_rules *rules)
{
	ft_error(str, rules);
	return (0);
}

int	sem_error_cleanup(t_rules *rules)
{
	sem_close(rules->sem_forks);
	sem_close(rules->sem_write);
	sem_close(rules->sem_philo_full);
	sem_close(rules->sem_philo_dead);
	sem_close(rules->sem_stop);
	unlink_global_sems();
	return (ft_error("Could not create semaphore.", rules));
}
