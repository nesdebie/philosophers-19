/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:43:13 by nesdebie          #+#    #+#             */
/*   Updated: 2023/07/06 00:25:52 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* contains_only_digits:
*	Checks if a string contains only digits 0 - 9.
*	Returns 1 if the string only contains digits.
*	Returns 0 if the string contains a character that is not a digit.
*/
static int	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* integer_atoi:
*	Converts a digit-only string into a positive integer.
*	Returns the converted number between 0 and INT MAX.
*	Returns -1 if the converted number exceeds INT MAX.
*/
int	integer_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/* is_valid_input:
*	Checks if all required arguments are valid, i.e. is a string of
*	digits only, which does not exceed INT MAX. Also checks if the number
*	of philosophers is valid (between 1 and MAX_PHILOS).
*	Returns 1 if all arguments are valid, 0 if one of them is invalid.
*/
int	is_valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!contains_only_digits(av[i]))
			return (error_msg("%s invalid input: %s: not a valid unsigned integer between 0 and 2147483647.\n", av[i], 0));
		nb = integer_atoi(av[i]);
		if (i == 1 && (nb <= 0))
			return (error_msg("%s invalid input: there must be between 1 and %s philosophers.\n", "Too many philosophers", 0));
		if (i != 1 && nb == -1)
			return (error_msg("%s invalid input: %s: not a valid unsigned integer between 0 and 2147483647.\n", av[i], 0));
		i++;
	}
	return (1);
}
