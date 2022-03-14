/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multibrot_set.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 20:29:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/14 17:47:13 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "constants.h"
#include "defs.h"
#include "bonus.h"
#include "libft.h"

static t_color	multibrot_escape(long double x0, long double y0, t_gui *gui)
{
	t_complex	z;
	int			i;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4 && i < gui->fractal.max_it)
	{
		z = complex_pow(z, gui->fractal.u_vars.exp);
		z.re += x0;
		z.im += y0;
		i++;
	}
	return (pallette(i, gui->fractal.max_it));
}

// z = z^a + c (where c is each pixel, and z starts at 0, a is a constant)
void	draw_multibrot(
			t_gui *gui, long double x, long double y, long double zoom)
{
	int				px;
	int				py;
	long double		x0;
	long double		y0;

	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = y + gui->fractal.scalar * zoom * (py - gui->canvas.height / 2);
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = x + gui->fractal.scalar * zoom * (px - gui->canvas.width / 2);
			gui_set_pixel(px, py, multibrot_escape(x0, -y0, gui), gui);
			px++;
		}
		py++;
	}
}

int	init_multibrot_set(t_gui *gui, char *args[], int argc)
{
	t_fractal	f;

	if (argc < 1 || argc > 2)
		return (0);
	f.e_type = MULTIBROT;
	if (!ft_atodl_strict(args[0], &f.u_vars.exp))
		return (0);
	f.max_it = 128;
	if (argc > 1 && !ft_atoi_strict(args[1], &f.max_it))
		return (0);
	f.zoom = 1;
	f.from_x = -2.5;
	f.to_x = 2.5;
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
