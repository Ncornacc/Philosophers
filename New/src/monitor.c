/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:55:30 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 13:09:03 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int everyone_full(t_philo *philo)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < philo->info->philo_num)
    {
        pthread_mutex_lock(&philo[i].eating);
        if (philo[i].has_eat_count >= \
			philo->info->eating_count)
			count += 1;
        pthread_mutex_unlock(&philo[i].eating);
        i++;
    }
    if (count == philo->info->philo_num)
    {
        philo->info->everyone_full = 1;
        return (1);
    }
    return (-1);
}

int loop(t_philo *philo, int i)
{
    while (i < philo->info->philo_num)
    {
        pthread_mutex_lock(&philo[i].eating);
        philo[i].time_current = get_time() - philo->info->start_time;
        if (philo[i].time_current > philo[i].time_for_eat)
        {
            pthread_mutex_lock(&philo->info->mutex_lock);
            philo->info->philo_dead = 1;
            pthread_mutex_unlock(&philo->info->mutex_lock);
			pthread_mutex_unlock(&philo[i].eating);
			philo_died(philo, philo[i].id);
			return (1);
        }
        pthread_mutex_unlock(&philo[i].eating);
		pthread_mutex_lock(&philo->info->mutex_lock);
		if (philo->info->eating_count != -1 \
			&& everyone_full(philo) == 1)
		{
			pthread_mutex_unlock(&philo->info->mutex_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->info->mutex_lock);
		i++;
    }
    return (0);
}

void    monitoring(t_philo *philo)
{
    if (philo->info->philo_num == 1)
        return ;
    while (1)
    {
        if(loop(philo, 0) == 1)
            return ;
        usleep(350 * 1000);
    }
    return ;
}

