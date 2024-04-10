/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:46:45 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 13:27:07 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_steal_fork(t_philo *philo, int id)
{
	int	check;

	if (philo->id == philo->info->philo_num)
	{
		pthread_mutex_lock(philo->right_fork);
		printing(philo, id, GREEN"has taken a fork "DEF_COLOR);
		pthread_mutex_lock(philo->left_fork);
		printing(philo, id, GREEN"has taken a fork "DEF_COLOR);
		check = philo_eating(philo, id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printing(philo, id, GREEN"has taken a fork "DEF_COLOR);
		pthread_mutex_lock(philo->right_fork);
		printing(philo, id, GREEN"has taken a fork "DEF_COLOR);
		check = philo_eating(philo, id);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (check);
}

int	philo_eating(t_philo *philo, int id)
{
	if (printing(philo, id, CYAN"is eating") == -1)
		return (-1);
	pthread_mutex_lock(&philo->eating);
	philo->time_for_eat = (get_time() - philo->info->start_time) \
		+ philo->info->time_to_die;
	philo->has_eat_count += 1;
	pthread_mutex_unlock(&philo->eating);
	sleep_function(philo->info->time_to_eat, philo);
	return (1);
}

int	philo_thinking(t_philo *philo, int id)
{
	if (printing(philo, id, YELLOW"is thinking "DEF_COLOR) == -1)
		return (-1);
	return (1);
}

int	philo_sleeping(t_philo *philo, int id)
{
	if (printing(philo, id, BLUE"is sleeping"DEF_COLOR) == -1)
		return (-1);
	sleep_function(philo->info->time_to_sleep, philo);
	return (TRUE);
}

int	philo_died(t_philo *philo, int id)
{
	long	time;

	pthread_mutex_lock(&philo->info->death_lock);
	time = get_time() - philo->info->start_time;
	printf("%lu %i is dead\n"DEF_COLOR, time, id);
	pthread_mutex_unlock(&philo->info->death_lock);
	return (TRUE);
}
