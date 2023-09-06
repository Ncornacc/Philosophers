/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 14:35:22 by ncornacc      #+#    #+#                 */
/*   Updated: 2022/10/06 12:40:40 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (!((c > 96 && c < 123) || (c > 64 && c < 91)))
		return (0);
	else
		return (1);
}
