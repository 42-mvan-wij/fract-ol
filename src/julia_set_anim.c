/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia_set_anim.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 11:22:53 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/14 17:42:20 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "constants.h"
#include "defs.h"
#include "libft.h"
#include "bonus.h"

static t_color	julia_anim_escape(long double z_re, long double z_im, t_gui *gui)
{
	long double	x2;
	long double	y2;
	int			i;

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

#include <stdio.h>
// z = z² + c (where z is each pixel)
void	draw_julia_anim(t_gui *gui, long double x, long double y, long double zoom)
{
	int				px;
	int				py;
	long double			x0;
	long double			y0;
	static long double  angle = 0;
	t_complex		c = {.re = gui->fractal.u_vars.c_re, .im = gui->fractal.u_vars.c_im};
	t_complex		c0 = c;

	c = complex_pow(c, angle);
	angle += M_PI_4 / 8;
	gui->fractal.u_vars.c_re = c.re;
	gui->fractal.u_vars.c_im = c.im;
	printf("re: %Lf, im: %Lf\n", c.re, c.im);
	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = y + gui->fractal.scalar * zoom * (py - gui->canvas.height / 2);
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + gui->fractal.scalar * zoom * (px - gui->canvas.width / 2);
			gui_set_pixel(px, py, julia_anim_escape(x0, -y0, gui), gui);
			px++;
		}
		py++;
	}
	gui->fractal.u_vars.c_re = c0.re;
	gui->fractal.u_vars.c_im = c0.im;
}

int	init_julia_anim_set(t_gui *gui, char *args[], int argc)
{
	t_fractal	f;

	if (argc < 2 || argc > 3)
		return (0);
	f.e_type = JULIA_ANIM;
	if (!ft_atodl_strict(args[0], &f.u_vars.c_re))
		return (0);
	if (!ft_atodl_strict(args[1], &f.u_vars.c_im))
		return (0);
	f.max_it = 1024;
	if (argc > 2 && !ft_atoi_strict(args[2], &f.max_it))
		return (0);
	f.zoom = 1;
	f.from_x = -1.5;
	f.to_x = 1.5;
	f.from_y = -1;
	f.to_y = 1;
	f.x_pos = (f.from_x + f.to_x) / 2;
	f.y_pos = (f.from_y + f.to_y) / 2;
	f.x_size = fabsl(f.to_x - f.from_x);
	f.y_size = fabsl(f.to_y - f.from_y);
	f.scalar = fmaxl(f.x_size / gui->canvas.width,
			f.y_size / gui->canvas.height);
	gui->fractal = f;
	return (1);
}
