/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/18 11:22:00 by aguay            ###   ########.fr       */
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
	while (true)
	{
		if (philo_died(toute) == true)
			return ;
		if (philos_won(toute) == true)
			return ;
	}
}

void	ft_run_philo(t_toutexd *toute)
{
	pthread_t	thread[2000];
	t_philo		**p_array;
	int			i;

	p_array = malloc(sizeof(t_philo *) * toute->nb_philo);
	init_p_array(toute, p_array);
	start_thread(thread, p_array, toute);
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
	free(p_array);
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
