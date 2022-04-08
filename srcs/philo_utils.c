/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 15:01:48 by aguay            ###   ########.fr       */
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

bool	eat_pair(t_toutexd *toute)
{
	if (toute->eat_goal)
		return (false);
	return (true);
}

bool	eat_impair(t_toutexd *toute)
{
	if (toute->eat_goal)
		return (false);
	return (true);
}