/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandelbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 16:32:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/22 18:00:33 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "constants.h"
#include "defs.h"

t_color	mandelbrot_escape(double x0, double y0, int max_i)
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
		y1 = 2 * x1 * y1 + y0;
		x1 = x2 - y2 + x0;
		x2 = x1 * x1;
		y2 = y1 * y1;
		i++;
	}
	return (pallette(i, max_i));
}

void	draw_mandelbrot(t_gui *gui, double x, double y, double zoom, int max_i)
{
	const double	scalar = fmax(3.5 / gui->canvas.width, 2.0 / gui->canvas.height);
	int				px;
	int				py;
	double			x0;
	double			y0;

	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = y + (((double)py * scalar) - 1.0) * zoom;

		// y0 = (((double)py + y) * scalar - 1) * zoom;
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + (((double)px * scalar) - 1.75) * zoom;
			// x0 = (((double)px + x) * scalar - 2.5) * zoom;
			gui_set_pixel(px, py, mandelbrot_escape(x0, y0, max_i), gui);
			px++;
		}
		py++;
	}
}
