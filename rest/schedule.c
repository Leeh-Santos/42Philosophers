/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:56:51 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/14 10:36:04 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	sleep_it(t_philo *phi)
{
	int	time;
	int sum;

	time = get_time();
	sum = 0;
	printer(phi, "is sleeping");
	while (sum <= info()->sleep_time)
		sum = get_time() - time;
	
}


void	eat(t_philo *philo, int der, int izq)
{
	int	time;
	int sum;

	time = get_time();
	sum = 0;
	printer(philo, "is eating");
	philo->nb_ate++;
	while (sum <= info()->eat_time) // trava
		sum = get_time() - time;
	philo->last_meal = get_time();
	pthread_mutex_lock(&info()->fork[der].mtx_fork); //return forks
	info()->fork[der].fork_slot = 1;
	pthread_mutex_unlock(&info()->fork[der].mtx_fork);
	pthread_mutex_lock(&info()->fork[izq].mtx_fork);
	info()->fork[izq].fork_slot = 1;
	pthread_mutex_unlock(&info()->fork[izq].mtx_fork);
	philo->nb_fork = 0;
 
}

void	takeit(t_philo *phi, int i)
{
	pthread_mutex_lock(&info()->fork[i].mtx_fork);
	if (info()->fork[i].fork_slot == 1)
	{
		info()->fork[i].fork_slot = 0;
		phi->nb_fork++;
		printer(phi, "has taken a fork");
	}
	pthread_mutex_unlock(&info()->fork[i].mtx_fork);				
}
 
void eat_it(t_philo *philo)
{
    int izq;
    int der;

    der = philo->philo_id - 1;
    izq = philo->philo_id - 2; //indexes
    if (der == 0) //first philo
        izq = info()->philo_total - 1;

    if (!died() && !starve(philo))
    {
        takeit(philo, der);
        takeit(philo, izq);
		if(philo->nb_fork == 2)
			eat(philo, der, izq);
    }
	
} 
