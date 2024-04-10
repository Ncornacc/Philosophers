/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:18:40 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 13:12:02 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


int	initialize_mutexes(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->philo_num)
	{
		if (pthread_mutex_init(&(info->forks[index]), NULL) == -1)
			return (-1);
		if (pthread_mutex_init(&info->philo[index].eating, \
			NULL) == -1)
			return (-1);
		index++;
	}
	if (pthread_mutex_init(&info->mutex_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&info->print_lock, NULL) == -1)
		return (-1);
	return (1);
}

void	fork_initialize(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->philo_num)
	{
		info->philo[index].left_fork = &(info->forks[index]);
		if ((index + 1) == info->philo_num)
			info->philo[index].right_fork = &(info->forks[0]);
		else
			info->philo[index].right_fork = \
				&(info->forks[index + 1]);
		index++;
	}
	return ;
}

void	initialize_data(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->philo_num)
	{
		info->philo[index].id = index + 1;
		info->philo[index].info = info;
		info->philo[index].time_for_eat = info->time_to_die;
		info->philo[index].has_eat_count = 0;
		info->philo[index].time_current = 0;
		index++;
	}
	fork_initialize(info);
	return ;
}

int	initialize_variables(t_info *info)
{
	info->philo = malloc(info->philo_num \
		* sizeof(t_philo));
	if (!info->philo)
		return (-1);
	info->forks = malloc(info->philo_num \
		* sizeof(pthread_mutex_t));
	if (!info->forks)
		return (-1);
	if (initialize_mutexes(info) == -1)
		return (-1);
	initialize_data(info);
	info->fail_thread = -1;
	return (1);
}

int	initialize_threads(t_info *info)
{
	int		index;

	index = 0;
	if (initialize_variables(info) == -1)
		return (-1);
	pthread_mutex_lock(&info->mutex_lock);
	while (index < info->philo_num)
	{
		if (pthread_create(&info->threads[index], NULL, \
			&thread_loop, &(info->philo[index])) != 0)
		{
			info->fail_thread = 1;
			pthread_mutex_unlock(&info->mutex_lock);
			end_threads(info->philo,  index);
			return (-1);
		}
		index++;
	}
	info->start_time = get_time();
	pthread_mutex_unlock(&info->mutex_lock);
	usleep((info->time_to_die / 3) * 1000);
	monitoring(info->philo);
	end_threads(info->philo, 0);
	return (1);
}
