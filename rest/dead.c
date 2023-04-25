/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:42:30 by learodri@st       #+#    #+#             */
/*   Updated: 2023/04/25 14:46:11 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	died(void)
{
	int	died;

	pthread_mutex_lock(&info()->deadmtx);
	died = info()->died;
	pthread_mutex_unlock(&info()->deadmtx);
	if (died)
		return (1);
	return (0);
}

int	starve(t_philo *phi)
{
	if (died())
		return (1);
	if ((get_time() - phi->last_meal) >= info()->die_time)
	{
		pthread_mutex_lock(&info()->deadmtx);
		info()->died++;
		if (info()->died)
		{
			printer(phi, "died");
		}
		pthread_mutex_unlock(&info()->deadmtx);
		return (1);
	}
	return (0);
}
