/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/09 12:36:06 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_toute(t_toutexd *toute, int argc, char **argv)
{
	toute->nb_philo = ft_atoi(argv[1]);
	if (gettimeofday(&toute->s_time, NULL) == -1)
	{
		write(2, "Error : Unable to setup start time.\n", 36);
		return ;
	}
	toute->philo1 = initialise_philo(argv);
	init_fork(*toute);
	if (argc == 6)
		toute->eat_goal = ft_atoi(argv[5]);
	else
		toute->eat_goal = -1;
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
	temp->time_to_eat = ft_atoi(argv[3]);
	temp->time_to_sleep = ft_atoi(argv[4]);
	temp->s_time = gettimeofday()
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
	start->philo_nb = 1;
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

void	init_fork(t_toutexd toute)
{
	t_philo	*temp;
	t_philo	*start;

	temp = toute.philo1;
	start = temp;
	while (temp != start && temp->left_fork != NULL)
	{
		if (temp->prev->right_fork != NULL)
			temp->left_fork = temp->prev->right_fork;
		temp->right_fork = malloc(sizeof(t_fork));
		pthread_mutex_init(&temp->right_fork->mutex, NULL);
		temp = temp->next;
	}
	temp->left_fork = temp->prev->right_fork;
}