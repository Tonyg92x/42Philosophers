/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:51:26 by aguay             #+#    #+#             */
/*   Updated: 2022/04/08 13:10:36 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(struct timeval	s_time)
{
	struct timeval	a_time;

	if (gettimeofday(&a_time, NULL) == -1)
	{
		write(2, "Failed to read timestamp.\n", 26);
		return (-1);
	}
	return (a_time.tv_usec - s_time.tv_usec);
}

void*	ft_eat()
{
	int	*i;

	i = malloc(sizeof(int));
	*i = 0;
	printf("Eating\n");
	return ((void *) i);
}

void	ft_run_philo(t_toutexd toute)
{
	pthread_t	thread[toute.nb_philo];
	int			i;
	int			*result;

	i = 0;
	while (i < toute.nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &ft_eat, NULL) != 0)
		{
			write(2, "Error : Couldnt create a thread.\n", 33);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < toute.nb_philo)
	{
		if (pthread_join(thread[i], (void **) &result) != 0)
		{
			write(2, "Error : Couldnt wait for a thread.\n", 35);
			return ;
		}
		if ((*result) == 0)
			printf("Philo %d has done eating\n", i + 1);
		free(result);
		i++;
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
	ft_run_philo(toute);
	free_mem(toute.philo1, ft_atoi(argv[1]));
	pthread_mutex_destroy(&toute.mutex);
	return (0);
}
