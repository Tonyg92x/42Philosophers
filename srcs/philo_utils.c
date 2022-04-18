/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 12:29:14 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_timestamp(struct timeval s_time)
{
	struct timeval	a_time;
	long long int	s_ms;
	long long int	a_ms;

	gettimeofday(&a_time, NULL);
	s_ms = (s_time.tv_sec * 1000) + (s_time.tv_usec / 1000);
	a_ms = (a_time.tv_sec * 1000) + (a_time.tv_usec / 1000);
	return (a_ms - s_ms);
}

bool	is_alive(t_philo *philo, char c)
{
	long long int	a_time;

	a_time = get_timestamp((*philo->s_time));
	if (c == 'e')
		philo->death_timer = philo->death_timer - (a_time - philo->last_eat);
	if (philo->death_timer < 0)
	{
		philo->time_to_die = -1;
		philo->death_timer = a_time;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (false);
	}
	return (true);
}

void	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (is_alive(philo, 'e') == false)
		return ;
	printf("%lld %d has taken a fork\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	philo->ate_time++;
}

void	eat_mofo(t_philo *philo)
{
	if (philo->on == false)
		return ;
	take_a_fork(philo);
	usleep(1000);
	if (philo->on == false)
		return ;
	printf("%lld %d is eating\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	usleep(philo->time_to_eat * 1000);
	philo->last_eat = get_timestamp((*philo->s_time));
	philo->death_timer = philo->time_to_die;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	if (philo->on == false)
		return ;
	printf("%lld %d is sleeping\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	if (is_alive_while(philo,
			get_timestamp((*philo->s_time)) + philo->time_to_sleep) == false)
		return ;
	if (philo->on == false)
		return ;
	ft_think(philo);
}
