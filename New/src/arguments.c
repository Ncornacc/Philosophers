/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arguments.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:18:41 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/04/10 13:04:40 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int digit(char *str)
{
    int i;

    i = 0;
    if (str[0] == '\0')
		return (-1);
	if (str[0] == '-')
		return (-1);
	if (str[0] == '0')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (1);
}

int overflow(char *str)
{
    int     i;
    char    *line;
    
    i = 0;
    if (ft_strlen(str) > 10)
        return (-1);
     if (ft_strlen(str) < 10)
        return (1);
    line = malloc(11 * sizeof(char));
    if (!str)
        return (-1);
    ft_strcpy(line, "2147483647");
    while (str[i])
    {
        if (str[i] > line[i])
        {
            free(str);
            return (-1);
        }
        i++;
    }
    free(line);
    return (1);
}

int check(char **argv)
{
    int i;

    i = 1;
    while (argv[i])
    {
        if (digit(argv[i]) == -1)
            return (-1);
        if (overflow(argv[i]) == -1)
            return (-1);
        i++;
    }
    return (1);
}

int check_arguments(int argc, char **argv)
{
    if (argc < 5)
		return (-1);
	if (argc > 6)
		return (-1);
	if (check(argv) == -1)
		return (-1);
	return (1);
}



int initialize_struct(char **argv, t_info *info)
{
    info->philo_num = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    info->philo_dead = -1;
    info->philo_full = -1;
    info->everyone_full = 0;
    if (argv[5])
        info->eating_count = ft_atoi(argv[5]);
    else
        info->eating_count = -1;
    return (1);
    
}