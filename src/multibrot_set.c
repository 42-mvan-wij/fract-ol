/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multibrot_set.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 20:29:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/26 20:34:23 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "constants.h"
#include "defs.h"
#include "bonus.h"

static t_color	multibrot_escape(double x0, double y0, double d, int max_i)
{
	t_complex	z;
	int			i;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4 && i < max_i)
	{
		z = complex_pow(z, d);
		z.re += x0;
		z.im += y0;
		i++;
	}
	return (pallette(i, max_i));
}

// z = z² + c (where c is each pixel, and z starts at 0)
void	draw_multibrot(t_gui *gui, double x, double y, double d, double zoom, int max_i)
{
	int				px;
	int				py;
	double			x0;
	double			y0;

	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = y + (((double)py * gui->fractal.scalar) - gui->fractal.y_size / 2) * zoom;
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + (((double)px * gui->fractal.scalar) - gui->fractal.x_size / 2) * zoom;
			gui_set_pixel(px, py, multibrot_escape(x0, y0, d, max_i), gui);
			px++;
		}
		py++;
	}
}
