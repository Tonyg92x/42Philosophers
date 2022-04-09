/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:42:17 by aguay             #+#    #+#             */
/*   Updated: 2022/04/09 12:29:43 by aguay            ###   ########.fr       */
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

typedef struct fork
{
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct philo
{
	struct philo	*next;
	struct philo	*prev;
	struct fork		*left_fork;
	struct fork		*right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				ate_time;
	int				philo_nb;
	char			status;
	struct timeval	s_time;
}				t_philo;

typedef struct toutexd
{
	struct philo	*philo1;
	struct timeval	s_time;
	int				nb_philo;
	int				eat_goal;
}				t_toutexd;

t_philo		*initialise_philo(char **argv);
bool		args_valid(int argc, char **argv);
void		init_toute(t_toutexd *toute, int argc, char **argv);
int			get_timestamp(struct timeval s_time);
int			eat_mofo(t_philo *philo);
void		init_fork(t_toutexd toute);

//	Utils
int			ft_atoi(const char *str);
int			ft_isdigit(int character);
void		free_mem(t_philo *start, int nb_philo);


#endif
