/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 11:22:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 14:15:22 by mvan-wij      ########   odam.nl         */
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
#include "libft.h"

static t_color	julia_escape(double z_re, double z_im, t_gui *gui)
{
	double	x2;
	double	y2;
	int		i;

	x2 = z_re * z_re;
	y2 = z_im * z_im;
	i = 0;
	while (x2 + y2 <= 4 && i < gui->fractal.max_it)
	{
		z_im = (z_re + z_re) * z_im + gui->fractal.u_vars.c_im;
		z_re = x2 - y2 + gui->fractal.u_vars.c_re;
		x2 = z_re * z_re;
		y2 = z_im * z_im;
		i++;
	}
	return (pallette(i, gui->fractal.max_it));
}

// z = z² + c (where z is each pixel)
void	draw_julia(t_gui *gui, double x, double y, double zoom)
{
	int				px;
	int				py;
	double			x0;
	double			y0;

	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = y + gui->fractal.scalar * zoom * (py - gui->canvas.height / 2);
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + gui->fractal.scalar * zoom * (px - gui->canvas.width / 2);
			gui_set_pixel(px, py, julia_escape(x0, y0, gui), gui);
			px++;
		}
		py++;
	}
}

int	init_julia_set(t_gui *gui, char *args[], int argc)
{
	t_fractal	f;

	if (argc < 2)
		return (0);
	f.e_type = JULIA;
	f.u_vars.c_re = ft_atod(args[0]);
	f.u_vars.c_im = ft_atod(args[1]);
	f.max_it = 1024;
	if (argc > 2)
		f.max_it = ft_atoi(args[2]);
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
	return (1);
}
