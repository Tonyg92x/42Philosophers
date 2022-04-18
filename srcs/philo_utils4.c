/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 13:33:46 by aguay            ###   ########.fr       */
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

void	ft_think(t_philo *philo)
{
	int long long	dif;

	printf("%lld %d is thinking\n",
		get_timestamp((*philo->s_time)), philo->philo_nb);
	dif = philo->time_to_die - philo->time_to_eat - philo->time_to_sleep;
	if (dif < 1)
	{
		dif = -dif;
		philo->death_timer = get_timestamp((*philo->s_time)) + dif;
		usleep(dif * 1000);
		philo->time_to_die = -1;
		return ;
	}
}
