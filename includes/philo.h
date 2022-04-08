/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:42:17 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 12:28:35 by aguay            ###   ########.fr       */
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
	struct philo	*prev;
	int				time_to_die;
	int				ate_time;
	int				philo_nb;
	char			status;
}				t_philo;

typedef struct toutexd
{
	struct philo	*philo1;
	pthread_mutex_t	mutex;
	struct timeval	s_time;
	int				nb_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal;
}				t_toutexd;

t_philo		*initialise_philo(char **argv);
bool		args_valid(int argc, char **argv);
void		init_toute(t_toutexd *toute, int argc, char **argv);

//	Utils
int			ft_atoi(const char *str);
int			ft_isdigit(int character);
void		free_mem(t_philo *start, int nb_philo);


#endif
