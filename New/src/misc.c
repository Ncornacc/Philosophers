/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:55:11 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 10:59:36 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


long	get_time(void)
{
	struct timeval	current_time;
	long			c_time;

	gettimeofday(&current_time, NULL);
	c_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (c_time);
}

int	sleep_function(long time, t_philo *philo)
{
	long	wait_time;
	long	time_loop;

	usleep((time / 3));
	wait_time = get_time() - philo->info->start_time;
	wait_time += time;
	time_loop = get_time() - philo->info->start_time;
	while (wait_time >= time_loop)
	{
		time_loop = get_time() - philo->info->start_time;
		usleep(200);
	}
	return (1);
}

void	end_threads(t_philo *philo, int index)
{
	int	i;

	i = 0;
	if (index == 0)
	{
		while (index < philo->info->philo_num)
		{
			pthread_join(philo->info->threads[index], NULL);
			index++;
		}
	}
	else
	{
		while (i < index)
		{
			pthread_join(philo->info->threads[index], NULL);
			i++;
		}
	}
	return ;
}

int	printing(t_philo *philo, int id, const char *str)
{
	long	time;

	pthread_mutex_lock(&philo->info->mutex_lock);
	if (philo->info->philo_dead == 1 \
		|| philo->info->everyone_full == 1)
	{
		pthread_mutex_unlock(&philo->info->mutex_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->info->mutex_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	time = get_time() - philo->info->start_time;
	printf("%lu %i %s\n", time, id, str);
	pthread_mutex_unlock(&philo->info->print_lock);
	return (1);
}