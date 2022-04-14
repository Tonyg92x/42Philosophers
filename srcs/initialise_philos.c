/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/14 12:36:04 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_toute(t_toutexd *toute, int argc, char **argv)
{
	int		i;
	t_philo	*temp;

	i = 0;
	toute->nb_philo = ft_atoi(argv[1]);
	toute->philo1 = initialise_philo(argv);
	init_fork(toute);
	if (argc == 6)
		toute->eat_goal = ft_atoi(argv[5]);
	else
		toute->eat_goal = -1;
	temp = toute->philo1;
	while (i < toute->nb_philo)
	{
		temp->s_time = &toute->s_time;
		temp = temp->next;
		i++;
	}
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
	temp->time_to_die = ft_atol(argv[2]);
	temp->time_to_eat = ft_atol(argv[3]);
	temp->time_to_sleep = ft_atol(argv[4]);
	temp->death_timer = ft_atol(argv[2]);
	temp->on = true;
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
	populate_this_shit(start, argv, 0);
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

void	init_fork(t_toutexd *toute)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo - 1)
	{
		if (philo->prev->right_fork != NULL)
			philo->left_fork = philo->prev->right_fork;
		fork = malloc(sizeof(t_fork));
		philo->right_fork = fork;
		pthread_mutex_init(&philo->right_fork->mutex, NULL);
		fork = NULL;
		philo = philo->next;
		i++;
	}
	if (philo->prev)
	{
		philo->left_fork = philo->prev->right_fork;
		fork = malloc(sizeof(t_fork));
		philo->right_fork = fork;
		philo->next->left_fork = fork;
	}
}
