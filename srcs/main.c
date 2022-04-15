/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/14 12:22:51 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_eat(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_nb % 2 == 0)
		usleep(philo->time_to_eat);
	while (philo->on == true)
		eat_mofo(philo);
	pthread_mutex_destroy(&philo->right_fork->mutex);
	pthread_mutex_destroy(&philo->left_fork->mutex);
	return (NULL);
}

static void	simu_done(t_toutexd *toute)
{
	t_philo	*philo;
	int		i;

	while (true)
	{
		philo = toute->philo1;
		i = 0;
		while (i < toute->nb_philo)
		{
			if (philo->time_to_die == -1)
			{
				end_simu(toute, 'l');
				return;
			}
			philo = philo->next;
			i++;
		}
		philo = toute->philo1;
		i = 0;
		while (i < toute->nb_philo)
		{
			if (toute->eat_goal < 1 || philo->ate_time < toute->eat_goal)
				break ;
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
	t_philo		*p_array[toute->nb_philo];
	int			i;

	i = 0;
	temp = toute->philo1;
	while (i < toute->nb_philo)
	{
		p_array[i] = temp;
		temp = temp->next;
		i++;
	}
	i = 0;
	gettimeofday(&toute->s_time, NULL);
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
	i = 0;
	if (toute->exit_status == 'l')
	{
		temp = toute->philo1;
		while (i < toute->nb_philo)
		{
			if (temp->time_to_die == -1)
				printf("%lld %d died\n", temp->death_timer, temp->philo_nb);
			i++;
			temp = temp->next;
		}
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
		printf("%lld %d died\n", toute.philo1->time_to_die,
			toute.philo1->philo_nb);
		return (0);
	}
	ft_run_philo(&toute);
	free_mem(toute.philo1, ft_atoi(argv[1]));
	return (0);
}
