/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:09:34 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/13 16:40:18 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct	s_fork
{
	int				fork_slot;
	pthread_mutex_t	mtx_fork;
}t_fork;

typedef struct	s_philo
{
	int			nb_fork;
	int			philo_id;
	long int	last_meal;
	int			nb_ate;
	t_fork 		*fork;
	pthread_t		philo_thr;

}t_philo;

typedef struct	s_info
{
	int			died;
	int			must_eat;
	int			philo_total;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			nb_eat;
	long int	clock;
	t_philo 	*philo;
	t_fork 		*fork;
	pthread_mutex_t	deadmtx;

}t_info;


int			ft_atoi(char *str);
long int	get_time(void);
t_info		*info(void);
void eat_it(t_philo *philo);
int died(void);
void	printer(t_philo *phi, char *txt);
void	takeit(t_philo *phi, int i);
void eat_it(t_philo *philo);
int	starve(t_philo *phi);
void	sleep_it(t_philo *phi);

#endif
