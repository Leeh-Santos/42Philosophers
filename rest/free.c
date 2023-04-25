/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:15:09 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/25 14:43:55 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	free_it(void)
{
	int	i;

	i = 0;
	if (info()->fork)
	{
		while (i < info()->philo_total)
		{
			pthread_mutex_destroy(&info()->fork[i].mtx_fork);
			i++;
		}
		free(info()->fork);
	}
	pthread_mutex_destroy(&info()->deadmtx);
	if (info()->philo)
		free(info()->philo);
}
