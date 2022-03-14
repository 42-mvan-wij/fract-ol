/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atodl.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/11 00:37:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/14 17:47:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Converts @p str to a long double
 * @param str
 * @return
 */
long double	ft_atodl(char *str)
{
	long double	int_part;
	long double	float_part;
	int			is_neg;

	while (ft_isspace(*str))
		str++;
	int_part = (long double)ft_atoi(str);
	is_neg = (*str == '-');
	if (*str == '+' || is_neg)
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != '.' || !ft_isdigit(str[1]))
		return (int_part);
	str++;
	float_part = (long double)ft_atoi(str);
	while (ft_isdigit(*str))
	{
		str++;
		float_part /= (long double)10;
	}
	if (is_neg)
		return (int_part - float_part);
	return (int_part + float_part);
}
