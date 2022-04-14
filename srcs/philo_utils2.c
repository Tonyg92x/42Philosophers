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
