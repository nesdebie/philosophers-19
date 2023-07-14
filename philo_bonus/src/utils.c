/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:18:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/14 15:16:54 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char	*dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
	return (dst);
}

char	*ft_utoa(unsigned int nb, size_t len)
{
	char	*ret;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len] = 0;
	len--;
	while (nb % 10)
	{
		ret[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}

void	unlink_global_sems(void)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("fed");
	sem_unlink("dead");
	sem_unlink("stop");
}

int	set_threads(t_rules *rules)
{
	if (pthread_create(&rules->fed, NULL, &ft_all_fed, rules))
		return (ft_error("Could not create thread.\n", rules));
	if (pthread_create(&rules->starved, NULL, &ft_starve_to_death, rules))
		return (ft_error("Could not create thread.\n", rules));
	return (1);
}
