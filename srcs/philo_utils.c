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
	long long		start_ms;
	long long		now_ms;

	if (gettimeofday(&a_time, NULL) == -1)
	{
		write(2, "Failed to read timestamp.\n", 26);
		return (-1);
	}
	start_ms = (s_time.tv_sec * 1000) + s_time.tv_usec;
	now_ms = (a_time.tv_sec * 1000) + a_time.tv_usec;
	return (now_ms - start_ms);
}

bool	is_alive(t_philo *philo)
{
	struct timeval	b_time;
	int				last_meal;
	int				total_a;

	if (gettimeofday(&b_time, NULL) == -1)
	{
		write(2, "Failed to read timestamp.\n", 26);
		return (-1);
	}
	last_meal = (philo->last_eat.tv_sec * 1000) + philo->last_eat.tv_usec;
	total_a = (b_time.tv_sec * 1000) + b_time.tv_usec;
	if (total_a - last_meal > philo->time_to_die)
	{
		philo->time_to_die = -1;
		last_meal = (philo->s_time.tv_sec * 1000) + philo->s_time.tv_usec;
		philo->death_timer = total_a - last_meal;
		return (false);
	}
	return (true);
}

void	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	// if (philo->time_to_die == -1 || is_alive(philo) == false)
	// 	return;
	printf("%d %d is eating\n",get_timestamp(philo->s_time), philo->philo_nb);
	philo->ate_time++;
}

void	eat_mofo(t_philo *philo)
{
	take_a_fork(philo);
	usleep(philo->time_to_eat);
	gettimeofday(&philo->last_eat, NULL);
	printf("%d %d is sleeping\n", get_timestamp(philo->s_time), philo->philo_nb);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	usleep(philo->time_to_sleep);
	printf("%d %d is thinking\n",get_timestamp(philo->s_time), philo->philo_nb);
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
