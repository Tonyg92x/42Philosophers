/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:42:17 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 09:14:42 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>

typedef struct philo
{
	struct philo	*next;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				eat_goal;
	int				ate_time;
	int				philo_nb;
	char			status;
}				t_philo;

t_philo		*initialise_philo(int argc, char **argv);
bool		args_valid(int argc, char **argv);

//	Utils
long int	ft_atol(char	*string);
int			ft_atoi(const char *str);
int			ft_isdigit(int character);
void		free_mem(t_philo *start, int nb_philo);

#endif
