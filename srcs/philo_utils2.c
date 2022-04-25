/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/21 07:36:33 by aguay            ###   ########.fr       */
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
	exit_message(toute);
}

bool	is_alive_while(t_philo *philo, long long int time)
{
	long long int	will_d;
	long long int	actual_t;

	actual_t = get_timestamp((*philo->s_time));
	will_d = philo->death_timer - time;
	if (will_d < 1)
	{
		will_d = actual_t + philo->death_timer;
		while (actual_t < will_d)
		{
			usleep(1000);
			actual_t = get_timestamp((*philo->s_time));
		}
		philo->death_timer = will_d;
		philo->time_to_die = -1;
		return (false);
	}
	usleep(time * 1000);
	philo->death_timer -= time;
	return (true);
}
