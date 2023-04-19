/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:01:01 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/19 16:21:14 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

#include "philos.h"

t_info *info(void)
{
	static t_info info;
	return (&info);
}

void	*dale(void *args)
{
	t_philo *philo;

	philo = (t_philo*)args;
	if (philo->philo_id % 2 == 0)
		usleep(80000); // com 100 morre tudo os philo vao atropelando um ao outro -  +0000 vao infinito
	//!died() && !starve(philo)
	int i = 0;
	while (!died() && !starve(philo))
	{
		if(info()->must_eat) 
			if(philo->nb_ate == info()->nb_eat)
		eat_it(philo);
		if (starve(philo) || died())
			return NULL ;
		sleep_it(philo);
	}
	return (NULL);
}

void	simulation_init(void)
{
	int	i;


	i = -1;
	info()->philo = malloc(sizeof(t_philo) * info()->philo_total);
	info()->fork = malloc(sizeof(t_philo) * info()->philo_total);
	if (!info()->philo || !info()->fork)
		return ;
	info()->clock = get_time(); /// change here 
	while (++i < info()->philo_total)
	{
		info()->fork[i].fork_slot = 1;
		pthread_mutex_init(&info()->fork[i].mtx_fork, NULL);
	}

	i = -1;

	while (++i < info()->philo_total)
	{
		info()->philo[i].nb_ate = 0;
		info()->philo[i].nb_fork = 0;
		info()->philo[i].philo_id = i + 1;
		info()->philo[i].last_meal = info()->clock;//last meal
		pthread_create(&info()->philo[i].philo_thr, NULL,
		&dale, (void*)&info()->philo[i]);
	}
	i = -1;
	while (++i < info()->philo_total)
		pthread_join(info()->philo[i].philo_thr, NULL);

}

void	philo_parse(int argc, char* argv[])
{
	info()->philo_total = ft_atoi(argv[1]);
	info()->die_time = ft_atoi(argv[2]);
	info()->eat_time = ft_atoi(argv[3]);
	info()->sleep_time = ft_atoi(argv[4]);
	pthread_mutex_init(&info()->deadmtx, NULL);
	if (argc == 6)
	{
		info()->nb_eat = ft_atoi(argv[5]);
		info()->must_eat = 1;
	}
	else
		info()->nb_eat = 0;
	if (info()->philo_total >= 1 && info()->die_time > 0 &&
		info()->eat_time > 0 && info()->sleep_time > 0 && info()->nb_eat >= 0)
				simulation_init();
	else
		printf("negative args bro");
}

int		main(int argc, char *argv[])
{
	if (argc == 6 || argc == 5)
	{
		philo_parse(argc, argv);
		free_it();
	}
	else
		printf("wrong number of args dog");

    return 0;
}