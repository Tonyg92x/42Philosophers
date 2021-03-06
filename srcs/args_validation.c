/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 11:57:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	nb_philo_valid(char *arg)
{
	if (ft_atoi(arg) < 1)
	{
		write(2, "Error : Nombre de philosophe invalide.\n", 40);
		return (false);
	}
	return (true);
}

static bool	time_valid(char *arg)
{
	if (ft_atoi(arg) <= 0)
	{
		write(2, "Error : Time stamp invalide.\n", 29);
		return (false);
	}
	return (true);
}

static bool	ate_time_valid(char *arg)
{
	if (ft_atoi(arg) < 1)
	{
		write(2, "Error : Number of time to eat invalid\n", 38);
		return (false);
	}
	return (true);
}

static bool	only_num(int argc, char **argv)
{
	int	i;
	int	y;

	y = 1;
	while (y < argc)
	{
		i = 0;
		while (argv[y][i])
		{
			if (argv[y][i] >= '0' && argv[y][i] <= '9')
				i++;
			else
			{
				write(2, "Argument invalide.\n", 19);
				return (false);
			}
		}
		y++;
	}
	return (true);
}

bool	args_valid(int argc, char **argv)
{
	if (nb_philo_valid(argv[1]) == false)
		return (false);
	if (time_valid(argv[2]) == false)
		return (false);
	if (time_valid(argv[3]) == false)
		return (false);
	if (time_valid(argv[4]) == false)
		return (false);
	if (argc == 6 && ate_time_valid(argv[5]) == false)
		return (false);
	if (only_num(argc, argv) == false)
		return (false);
	return (true);
}
