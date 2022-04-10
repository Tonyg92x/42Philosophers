/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/09 12:33:10 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	ft_eat(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_nb % 2 == 0)
		usleep(philo->time_to_eat);
	while(philo->on == true)
		eat_mofo(philo);
	return (NULL);
}

static void	end_simu(t_toutexd *toute, char status)
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

static void	simu_done(t_toutexd *toute)
{
	t_philo	*philo;
	int		i;

	while (true)
	{
		i = 0;
		philo = toute->philo1;
		while (i < toute->nb_philo)
		{
			if (philo->time_to_die == -1)
			{
				toute->dead_philo = philo->philo_nb;
				end_simu(toute, 'l');
				return;
			}
			i++;
			philo = philo->next;
		}
		philo = toute->philo1;
		i = 0;
		while (i < toute->nb_philo)
		{
			if (toute->eat_goal < 1 || philo->ate_time < toute->eat_goal)
				break;
			if (i + 1 == toute->nb_philo)
			{
				end_simu(toute, 'w');
				return ;
			}
			philo = philo->next;
			i++;
		}
	}
}

void	ft_run_philo(t_toutexd *toute)
{
	pthread_t	thread[toute->nb_philo];
	t_philo		*temp;
	int			i;

	i = 0;
	gettimeofday(&toute->s_time, NULL);
	temp = toute->philo1;
	while (i < toute->nb_philo)
	{
		temp->s_time = toute->s_time;
		if (pthread_create(&thread[i], NULL, &ft_eat, temp) != 0)
		{
			write(2, "Error : Couldnt create a thread.\n", 33);
			return ;
		}
		temp = temp->next;
		i++;
	}
	simu_done(toute);
	i = 0;
	while (i < toute->nb_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			write(2, "Error : Couldnt wait for a thread.\n", 35);
			return ;
		}
		i++;
	}
	if (toute->exit_status == 'w')
		printf("Simulation won ! Every philosophers ate the eat goal.\n");
	if (toute->exit_status == 'l')
	{
		temp = toute->philo1;
		while (temp->time_to_die != 1)
			temp = temp->next;
		printf("%d %d died\n", temp->death_timer, temp->philo_nb);
	}
}

int	main(int argc, char **argv)
{
	t_toutexd		toute;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error : Nombre d'arguments invalide.\n", 37);
		return (0);
	}
	if (args_valid(argc, argv) == false)
		return (0);
	init_toute(&toute, argc, argv);
	if (toute.nb_philo < 2)
	{
		printf("%d %d died\n", toute.philo1->time_to_die, toute.philo1->philo_nb);
		return (0);
	}
	ft_run_philo(&toute);
	free_mem(toute.philo1, ft_atoi(argv[1]));
	return (0);
}
