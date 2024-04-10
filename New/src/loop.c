/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:41:44 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 13:26:14 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../philosophers.h"

int	one_philo_loop(t_philo *philo)
{
	int		boolean;
	long	time;
	long	time_wait;

	time = get_time() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->mutex_lock);
	time_wait = philo->time_for_eat;
	pthread_mutex_unlock(&philo->info->mutex_lock);
	boolean = 1;
	while (time_wait > time)
	{
		time = get_time() - philo->info->start_time;
		if (boolean == 1)
		{
			philo_thinking(philo, philo->id);
			printing(philo, philo->id, GREEN"has taken a fork" DEF_COLOR);
			boolean = -1;
		}
	}
	printf(PINK"%lu %i is dead\n"DEF_COLOR, time, philo->id);
	return (1);
}

void	*thread_loop(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(&philo->info->mutex_lock);
	if (philo->info->fail_thread == 1)
	{
		pthread_mutex_unlock(&philo->info->mutex_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->info->mutex_lock);
	if (philo->info->philo_num == 1)
		one_philo_loop(philo);
	else
	{
		if (philo->id % 2 == 0)
			operations_even(philo);
		else
			operations_odd(philo);
	}
	return (NULL);
}

int	operations_odd(t_philo *philo)
{
	while (1)
	{
		if (philo_sleeping(philo, philo->id) == -1)
			break ;
		if (philo_thinking(philo, philo->id) == -1)
			break ;
		if (philo_steal_fork(philo, philo->id) == -1)
			break ;
	}
	return (0);
}

int	operations_even(t_philo *philo)
{
	while (1)
	{
		if (philo_thinking(philo, philo->id) == -1)
			break ;
		if (philo_steal_fork(philo, philo->id) == -1)
			break ;
		if (philo_sleeping(philo, philo->id) == -1)
			break ;
	}
	return (0);
}

