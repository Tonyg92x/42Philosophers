/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 08:54:55 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	populate_this_shit(t_philo *temp, int argc, char **argv, int i)
{
	temp->philo_nb = i + 1;
	temp->ate_time = 0;
	temp->status = 'P';
	temp->time_to_die = ft_atol(argv[2]);
	temp->time_to_eat = ft_atol(argv[3]);
	temp->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		temp->eat_goal = ft_atoi(argv[5]);
}

t_philo	*initialise_philo(int argc, char **argv)
{
	int		i;
	t_philo	*temp;
	t_philo	*start;

	i = 1;
	start = malloc(sizeof(t_philo));
	if (!start)
		return (NULL);
	start->philo_nb = 1;
	populate_this_shit(start, argc, argv, 0);
	temp = start;
	while (i < ft_atoi(argv[1]))
	{
		temp->next = malloc(sizeof(t_philo));
		if (!temp->next)
		{
			free_mem(start, i);
			return (NULL);
		}
		populate_this_shit(temp->next, argc, argv, i);
		temp = temp->next;
		i++;
	}
	temp->next = start;
	return (start);
}

void	free_mem(t_philo *start, int nb_philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		temp = start;
		start = start->next;
		free(temp);
		i++;
	}
}
