/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:56:51 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/19 16:05:43 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	sleep_it(t_philo *phi)
{
	int	time;
	int sum;

	time = get_time();
	sum = 0;
	if (died())
		return ;
	printer(phi, "is sleeping");
	while (sum <= info()->sleep_time)
		sum = get_time() - time;
	if (starve(phi) || died()) //tava aqui
		return ;
	if (died())
		return 
	printer(phi, "is thinking");
	
}


void	eat(t_philo *philo, int der, int izq)
{
	int	time;
	int sum;
	

	time = get_time();
	sum = 0;
	if (died())
		return ;
	//if (!starve(philo)) - over protect
	usleep(100);
	printer(philo, "is eating");
	philo->nb_ate++;
	while (sum <= info()->eat_time && !starve(philo)) // trava
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
	//while (!starve(phi) && !died()) // TAVA WHILE ANTEStem que forcar ele toda hora se nao afeta o dead time
	while (!starve(phi))
	{
		pthread_mutex_lock(&info()->fork[i].mtx_fork);
		if (info()->fork[i].fork_slot == 1)
		{
			info()->fork[i].fork_slot = 0;
			phi->nb_fork++;
			printer(phi, "has taken a fork");
			pthread_mutex_unlock(&info()->fork[i].mtx_fork);
			break ;
		}
		else
			pthread_mutex_unlock(&info()->fork[i].mtx_fork);
	}				
}
 
void eat_it(t_philo *philo)
{
    int izq;
    int der;

    der = philo->philo_id - 1;
    izq = philo->philo_id - 2; 
    if (der == 0) //first philo
        izq = info()->philo_total - 1;

	/*izq = philo->philo_id - 1; 
	der = (philo->philo_id != info()->philo_total) * philo->philo_id;*/ 

   if (!died() && !starve(philo)) //&& !died()
   {
        takeit(philo, der); // problema aqui no while no inicio
        takeit(philo, izq);
		if(philo->nb_fork == 2)
			eat(philo, der, izq);
   }
	
} 
