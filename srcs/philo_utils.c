/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/09 12:26:43 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(struct timeval s_time)
{
	struct timeval	a_time;

	if (gettimeofday(&a_time, NULL) == -1)
	{
		write(2, "Failed to read timestamp.\n", 26);
		return (-1);
	}
	return (a_time.tv_usec - s_time.tv_usec);
}

int	eat_mofo(t_philo *philo)
{
	printf("Philo %d is eating\n", philo->philo_nb);
	usleep(100000);
	return (1);
}

void	free_mem(t_philo *start, int nb_philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		temp = start;
		if (temp->left_fork != NULL)
		{
			pthread_mutex_destroy(&temp->left_fork->mutex);
			free(temp->left_fork);
		}
		if (temp->right_fork != NULL)
		{
			pthread_mutex_destroy(&temp->right_fork->mutex);
			free(temp->right_fork);
		}
		start = start->next;
		free(temp);
		i++;
	}
}

// bool	goal_reach(t_toutexd *toute)
// {
// 	t_philo	*temp;
// 	int		i;

// 	i = 0;
// 	temp = toute->philo1;
	
// }