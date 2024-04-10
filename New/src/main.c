/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:13:01 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 10:37:08 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char **argv)
{
    t_info *info;

    if (check_arguments(argc, argv) == -1)
		return (print_error(("Error\nWrong arguments"), NULL));
	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!info)
		return (print_error(("Error\nAllocation of struct failed"), NULL));
	initialize_struct(argv, info);
	info->threads = malloc((info->philo_num) * sizeof(pthread_t));
	if (!info->threads)
		return (print_error(("Error\nAllocation of struct failed"), info));
	if (initialize_threads(info) == -1)
		return (print_error(("Error\nA thread failed"), info));
	free_struct(info);
	return (0);
}