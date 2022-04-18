/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 12:08:56 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_toutexd *toute)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo)
	{
		if (philo->time_to_die == -1)
		{
			end_simu(toute, 'l');
			return (true);
		}
		philo = philo->next;
		i++;
	}
	return (false);
}

bool	philos_won(t_toutexd *toute)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo)
	{
		if (toute->eat_goal < 1 || philo->ate_time < toute->eat_goal)
			break ;
		if (i + 1 == toute->nb_philo)
		{
			end_simu(toute, 'w');
			return (true);
		}
		philo = philo->next;
		i++;
	}
	return (false);
}

t_philo	*ft_quit(int i, t_philo *start)
{
	free_mem(start, i);
	return (NULL);
}

void	start_thread(pthread_t *thread, t_philo **p_array, t_toutexd *toute)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = toute->philo1;
	while (i < toute->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &ft_eat, p_array[i]) != 0)
		{
			write(2, "Error : Couldnt create a thread.\n", 33);
			return ;
		}
		usleep(10);
		i++;
	}
}

void	exit_message(t_toutexd *toute)
{
	int			i;
	int			y;
	t_philo		*philo;

	if (toute->exit_status == 'l')
	{
		i = 0;
		y = ft_smallest_dt(toute);
		philo = toute->philo1;
		while (y != philo->philo_nb)
			philo = philo->next;
		printf("%lld %d died\n",
			get_timestamp((*philo->s_time)), philo->philo_nb);
	}
}
