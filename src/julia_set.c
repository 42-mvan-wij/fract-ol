/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 11:22:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/27 17:15:00 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

static t_color	julia_escape(double z_re, double z_im, double c_re, double c_im, int max_i)
{
	double	x2;
	double	y2;
	int		i;

	x2 = z_re * z_re;
	y2 = z_im * z_im;
	i = 0;
	while (x2 + y2 <= 4 && i < max_i)
	{
		// z² + c
		// (a + bi)²
		// a² + 2abi - b²
		// (a² + b²; 2ab)

		// (a + bi)³
		// (a + bi)² * (a + bi)
		// (a² + 2abi - b²) * (a + bi)
		// (a³ + 2a²bi - ab² + a²bi - 2ab² - b³i)
		// (a³ - 3ab²; 3a²b - b³)
		z_im = (z_re + z_re) * z_im + c_im;
		z_re = x2 - y2 + c_re;
		x2 = z_re * z_re;
		y2 = z_im * z_im;
		i++;
	}
	return (pallette(i, max_i));
}

// z = z² + c (where z is each pixel)
void	draw_julia(t_gui *gui, double c_x, double c_y, double x, double y, double zoom, int max_i)
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
			gui_set_pixel(px, py, julia_escape(x0, y0, c_x, c_y, max_i), gui);
			px++;
		}
		py++;
	}
}

void	init_julia_set(t_gui *gui)
{
	t_fractal	f;

	f.e_type = JULIA;
	f.u_vars.c_re = -0.8;
	f.u_vars.c_im = 0.156;
	f.zoom = 1;
	f.from_x = -1.5;
	f.to_x = 1.5;
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
