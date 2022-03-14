/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atod_strict.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/11 00:37:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/10 17:32:08 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

void	ft_atod_strict_skipper(char *str, size_t *i, size_t *non_digits)
{
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
	if (str[*i] == '+' || str[*i] == '-')
	{
		(*non_digits)++;
		(*i)++;
	}
	while (ft_isdigit(str[*i]))
		(*i)++;
	if (str[*i] == '.')
	{
		(*i)++;
		(*non_digits)++;
	}
	while (ft_isdigit(str[*i]))
		(*i)++;
	while (ft_isspace(str[*i]))
	{
		(*non_digits)++;
		(*i)++;
	}
}

/**
 * Converts @p str to a double
 * @param str
 * @param result_ptr
 * @return
 */
bool	ft_atod_strict(char *str, double *result_ptr)
{
	size_t	i;
	size_t	non_digits;

	if (str == NULL)
		return (false);
	i = 0;
	non_digits = 0;
	ft_atod_strict_skipper(str, &i, &non_digits);
	if (i == non_digits || str[i] != '\0')
		return (false);
	*result_ptr = ft_atod(str);
	return (true);
}
