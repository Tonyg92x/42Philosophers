/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 12:34:44 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_toute(t_toutexd *toute, int argc, char **argv)
{
	toute->nb_philo = ft_atoi(argv[1]);
	toute->time_to_eat = ft_atoi(argv[2]);
	toute->time_to_sleep = ft_atoi(argv[3]);
	if (gettimeofday(&toute->s_time, NULL) == -1)
	{
		write(2, "Error : Unable to setup start time.\n", 36);
		return ;
	}
	toute->philo1 = initialise_philo(argv);
	if (argc == 6)
		toute->eat_goal = ft_atoi(argv[5]);
	pthread_mutex_init(&toute->mutex, NULL);
}

static t_philo	*ft_quit(int i, t_philo *start)
{
	free_mem(start, i);
	return (NULL);
}

static void	populate_this_shit(t_philo *temp, char **argv, int i)
{
	temp->philo_nb = i + 1;
	temp->ate_time = 0;
	temp->status = 'P';
	temp->time_to_die = ft_atoi(argv[2]);
}

t_philo	*initialise_philo(char **argv)
{
	int		i;
	t_philo	*temp;
	t_philo	*start;

	i = 1;
	start = malloc(sizeof(t_philo));
	if (!start)
		return (NULL);
	start->philo_nb = 0;
	temp = start;
	while (i < ft_atoi(argv[1]))
	{
		temp->next = malloc(sizeof(t_philo));
		if (!temp->next)
			return (ft_quit(i, start));
		populate_this_shit(temp->next, argv, i);
		temp->next->prev = temp;
		temp = temp->next;
		i++;
	}
	temp->next = start;
	start->prev = temp;
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
