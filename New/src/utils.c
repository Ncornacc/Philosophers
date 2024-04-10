/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:45:21 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/03/19 16:36:20 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

int	ft_atoi(char *str)
{
	int	index;
	int	numb;
	int	sum;

	index = 0;
	sum = 0;
	if (str[0] == '-')
		return (-1);
	while (str[index])
	{
		numb = str[index] - '0';
		sum = sum + numb;
		if (str[index + 1] != '\0')
			sum = sum * 10;
		index++;
	}
	return (sum);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	total;

	total = count * size;
	ptr = (void *) malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (total > 0)
	{
		ptr[i] = '\0';
		i++;
		total--;
	}
	return ((void *)ptr);
}
