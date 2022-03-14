/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 20:31:26 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/14 17:46:06 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "constants.h"

typedef struct s_complex
{
	long double	re;
	long double	im;
}	t_complex;

// t_complex	complex_mult(t_complex a, t_complex b);
t_complex	complex_from_angle(long double a, long double m);
long double	complex_mag(t_complex c);
t_complex	complex_pow(t_complex c, long double p);

#endif
