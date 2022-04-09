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
	int		*status;
	int		j;

	status = malloc(sizeof(int));
	*status = 1;
	j = 0;
	philo = arg;
	while((*status) == 1)
	{
		(*status) = eat_mofo(philo);
	}
	return ((void *) status);
}

void	ft_run_philo(t_toutexd toute)
{
	pthread_t	thread[toute.nb_philo];
	t_philo		*temp;
	int			i;
	int			j;
	int			*result;

	i = 0;
	j = 2;
	temp = toute.philo1;
	printf("Philo %d is eating\n", temp->philo_nb);
	while (i < toute.nb_philo)
	{
		if (j % 2 == 0)
			usleep(temp->time_to_eat / 2);
		if (pthread_create(&thread[i], NULL, &ft_eat, temp) != 0)
		{
			write(2, "Error : Couldnt create a thread.\n", 33);
			return ;
		}
		temp = temp->next;
		i++;
		j++;
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
			printf("Philo %d has done eating %d time.\n", i + 1, toute.eat_goal);
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
	return (0);
}
