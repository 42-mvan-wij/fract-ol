/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot_set.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 16:32:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/27 17:03:48 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "constants.h"
#include "defs.h"

static t_color	mandelbrot_escape(double x0, double y0, int max_i)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	int		i;

	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	i = 0;
	while (x2 + y2 <= 4 && i < max_i)
	{
		y1 = (x1 + x1) * y1 + y0;
		x1 = x2 - y2 + x0;
		x2 = x1 * x1;
		y2 = y1 * y1;
		i++;
	}
	return (pallette(i, max_i));
}

// z = z² + c (where c is each pixel, and z starts at 0)
void	draw_mandelbrot(t_gui *gui, double x, double y, double zoom, int max_i)
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
			gui_set_pixel(px, py, mandelbrot_escape(x0, y0, max_i), gui);
			px++;
		}
		py++;
	}
}

void	init_mandelbrot_set(t_gui *gui)
{
	t_fractal	f;

	f.e_type = MANDELBROT;
	f.zoom = 1;
	f.from_x = -2.5;
	f.to_x = 1;
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
