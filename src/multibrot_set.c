/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multibrot_set.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 20:29:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/27 17:24:04 by mvan-wij      ########   odam.nl         */
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
		y0 = y + (double)(py - gui->canvas.height / 2) * gui->fractal.scalar * zoom;
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + (double)(px - gui->canvas.width / 2) * gui->fractal.scalar * zoom;
			gui_set_pixel(px, py, multibrot_escape(x0, y0, d, max_i), gui);
			px++;
		}
		py++;
	}
}

void	init_multibrot_set(t_gui *gui)
{
	t_fractal	f;

	f.e_type = MULTIBROT;
	f.u_vars.exp = 2;
	f.zoom = 1;
	f.from_x = -2.5;
	f.to_x = 2.5;
	f.from_y = -1;
	f.to_y = 1;
	f.x_pos = (f.from_x + f.to_x) / 2;
	f.y_pos = (f.from_y + f.to_y) / 2;
	f.x_size = fabs(f.to_x - f.from_x);
	f.y_size = fabs(f.to_y - f.from_y);
	f.scalar = fmax(f.x_size / gui->canvas.width,
			f.y_size / gui->canvas.height);
	gui->fractal = f;
}
