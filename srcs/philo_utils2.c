/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/14 12:01:49 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_abs(long long int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
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

void	end_simu(t_toutexd *toute, char status)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo)
	{
		philo->on = false;
		i++;
		philo = philo->next;
	}
	toute->exit_status = status;
}

bool	is_alive_while(t_philo *philo, long long int lim)
{
	long long int	will_d;
	long long int	actual_t;
	bool			die;

	actual_t = get_timestamp((*philo->s_time));
	will_d = philo->death_timer - (lim - actual_t);
	if (will_d < 1)
	{
		die = true;
		will_d = actual_t + philo->death_timer;
	}
	else
		die = false;
	while (get_timestamp((*philo->s_time)) < lim)
	{
		if (die == true)
		{
			while (actual_t < will_d)
				usleep(1000);
			philo->time_to_die = -1;
			philo->death_timer = get_timestamp((*philo->s_time));;
			return (false);
		}
		usleep(1000);
	}
	philo->death_timer = philo->death_timer - philo->time_to_sleep;
	return (true);
}

bool	is_thinking(t_philo *philo)
{
	while (pthread_mutex_lock(&philo->right_fork->mutex) != 0)
	{
		usleep(1000);
		philo->death_timer--;
		if (philo->death_timer < 1)
		{
			philo->time_to_die = -1;
			philo->death_timer = get_timestamp((*philo->s_time));;
			return (false);
		}
	}
	while (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
	{
		usleep(1000);
		philo->death_timer--;
		if (philo->death_timer < 1)
		{
			philo->time_to_die = -1;
			philo->death_timer = get_timestamp((*philo->s_time));;
			return (false);
		}
	}
	return (true);
}