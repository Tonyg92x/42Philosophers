/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 07:42:17 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 13:39:04 by aguay            ###   ########.fr       */
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
	struct timeval	*s_time;
	long long int	last_eat;
	long long int	death_timer;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	int				ate_time;
	int				philo_nb;
	bool			on;
}				t_philo;

typedef struct toutexd
{
	struct philo	*philo1;
	struct timeval	s_time;
	int				nb_philo;
	int				eat_goal;
	char			exit_status;
	int				dead_philo;
}				t_toutexd;

t_philo			*initialise_philo(char **argv);
bool			args_valid(int argc, char **argv);
void			init_toute(t_toutexd *toute, int argc, char **argv);
long long int	get_timestamp(struct timeval s_time);
void			eat_mofo(t_philo *philo);
void			init_fork(t_toutexd *toute);
void			wait_time(long long int time_to_wait, t_philo *philo);
void			end_simu(t_toutexd *toute, char status);
bool			is_alive_while(t_philo *philo, long long int lim);
bool			is_thinking(t_philo *philo);
bool			philo_died(t_toutexd *toute);
bool			philos_won(t_toutexd *toute);
t_philo			*ft_quit(int i, t_philo *start);
void			*ft_eat(void *arg);
void			init_p_array(t_toutexd *toute, t_philo **p_array);
void			start_thread(pthread_t *thread, t_philo **p_array,
					t_toutexd *toute);
void			exit_message(t_toutexd *toute);
int				ft_smallest_dt(t_toutexd *toute);
void			ft_think(t_philo *philo);

//	Utils
int				ft_atoi(const char *str);
long long int	ft_atol(char	*string);
int				ft_isdigit(int character);
void			free_mem(t_philo *start, int nb_philo);
long long int	ft_abs(long long int nb);

#endif
