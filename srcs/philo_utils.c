/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/27 11:24:23 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_smallest_dt(t_toutexd *toute)
{
	t_philo		*philo;
	int			i;
	int			y;
	int			y_t;

	i = 0;
	y_t = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo)
	{
		if (philo->time_to_die == -1)
		{
			if (y_t == 0 || philo->death_timer < y_t)
			{
				y = philo->philo_nb;
				y_t = philo->death_timer;
			}
		}
		philo = philo->next;
		i++;
	}
	return (y);
}

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

void	take_a_fork(t_philo *philo)
{
	if (philo->on == false)
		return ;
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (get_timestamp((*philo->s_time)) > philo->last_eat
		+ philo->time_to_die)
	{
		ft_die(philo);
		return ;
	}
	printf("%lld %d has taken a fork\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	philo->ate_time++;
	philo->last_eat = (get_timestamp((*philo->s_time)) + (1 * philo->ate_time));
}

void	eat_mofo(t_philo *philo)
{
	if (philo->on == false)
		return ;
	take_a_fork(philo);
	if (philo->on == false)
		return ;
	printf("%lld %d is eating\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	philo->death_timer = philo->time_to_die;
	if (is_alive_while(philo, philo->time_to_eat) == false)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return ;
	}
	philo->death_timer = philo->time_to_die - philo->time_to_eat;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	if (philo->on == false)
		return ;
	printf("%lld %d is sleeping\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	if (is_alive_while(philo, philo->time_to_sleep) == false)
		return ;
	if (philo->on == false)
		return ;
}
