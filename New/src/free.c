/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:47:15 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 10:39:38 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	print_error(char *str, t_info *info)
{
	if (info)
		free_struct(info);
	printf(RED"%s\n"DEF_COLOR, str);
	return (-1);
}

void	delete_mutexes(t_info *info)
{
    int	index;

	index = 0;
	while (index < info->philo_num)
	{
		pthread_mutex_destroy(info->philo[index].left_fork);
		pthread_mutex_destroy(info->philo[index].right_fork);
		pthread_mutex_destroy(&info->philo[index].eating);
		index++;
	}
	pthread_mutex_destroy(&info->mutex_lock);
	pthread_mutex_destroy(&info->death_lock);
	pthread_mutex_destroy(&info->print_lock);
}

void    free_struct(t_info *info)
{
    delete_mutexes(info);
    free(info->threads);
    free(info->forks);
    free(info->philo);
    free(info);
}