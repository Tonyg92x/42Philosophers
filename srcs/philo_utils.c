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

void	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	printf("Philo %d has taken both fork.\n", philo->philo_nb);
}

int	eat_mofo(t_philo *philo)
{
	take_a_fork(philo);
	printf("Philo %d is eating\n", philo->philo_nb);
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	printf("Philo %d has drop fork\n", philo->philo_nb);
	philo->ate_time++;
	printf("Philo %d is sleeping\n", philo->philo_nb);
	usleep(philo->time_to_sleep);
	printf("Philo %d is thinking\n", philo->philo_nb);
	return (1);
}

void	free_mem(t_philo *start, int nb_philo)
{
	t_philo	*temp;
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&start->right_fork->mutex);
		free(start->right_fork);
		temp = start;
		start = start->next;
		free(temp);
		i++;
	}
}
