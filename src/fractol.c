/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:39:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/14 17:50:04 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // printf, perror
#include <string.h> // strerror
#include <fcntl.h> // open
#include <unistd.h> // close, read, write
#include <stdlib.h> // malloc, free, exit
#include <math.h> // yay

#include "constants.h"
#include "mlx.h"
#include "libft.h"
#include "defs.h"

t_gui	create_gui(int width, int height)
{
	t_gui	gui;

	gui.mlx = mlx_init();
	gui.canvas.img = mlx_new_image(gui.mlx, width, height);
	gui.canvas.width = width;
	gui.canvas.height = height;
	gui.canvas.data = mlx_get_data_addr(gui.canvas.img, &gui.canvas.bpp,
			&gui.canvas.line_len, &gui.canvas.endian);
	gui.do_redraw = 1;
	gui.is_redrawing = 0;
	return (gui);
}

void	create_window(t_gui *gui)
{
	static char	*title_table[] = {
	[MANDELBROT] = "fract-ol: Mandelbrot set",
	[JULIA] = "fract-ol: Julia set",
	[MULTIBROT] = "fract-ol: Multibrot set",
	[JULIA_ANIM] = "fract-ol: Julia set (Animated)",
	};

	gui->window = mlx_new_window(gui->mlx, gui->canvas.width,
			gui->canvas.height, title_table[gui->fractal.e_type]);
}

int	parse_args(char *argv[], int argc, t_gui *gui)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
	{
		*gui = create_gui(1400, 800);
		return (init_mandelbrot_set(gui, &argv[2], argc - 2));
	}
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		*gui = create_gui(1200, 900);
		return (init_julia_set(gui, &argv[2], argc - 2));
	}
	else
		return (parse_args_bonus(argv, argc, gui));
}

void	draw_fractal(t_gui *gui)
{
	if (gui->fractal.e_type == MANDELBROT)
		draw_mandelbrot(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
	else if (gui->fractal.e_type == JULIA)
		draw_julia(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
	else
		draw_fractal_bonus(gui);
}

#ifndef BONUS
# define USAGE_TEXT "\
 <mandelbrot | julia> <fractal arguments> [max iterations]\n\
Fractal arguments:\n\
\tmandelbrot: -\n\
\tjulia: <real> <imaginary>\n"
#else
# define USAGE_TEXT "\
 <mandelbrot | julia | multibrot> <fractal arguments> [max iterations]\n\
Fractal arguments:\n\
\tmandelbrot: -\n\
\tjulia: <real> <imaginary>\n\
\tmultibrot: <exponent>\n"
#endif

int	main(int argc, char *argv[])
{
	t_gui	gui;

	if (!parse_args(argv, argc, &gui))
	{
		ft_putstr_fd("usage: ", STDOUT_FILENO);
		ft_putstr_fd(argv[0], STDOUT_FILENO);
		ft_putstr_fd(USAGE_TEXT, STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	create_window(&gui);
	mlx_hook(gui.window, CROSS_PRESS, CROSS_PRESS_MASK, close_hook, NULL);
	mlx_hook(gui.window, KEY_PRESS, KEY_PRESS_MASK, key_hook, &gui);
	mlx_hook(gui.window, BUTTON_PRESS, BUTTON_PRESS_MASK, button_hook, &gui);
	mlx_loop_hook(gui.mlx, loop_hook, &gui);
	mlx_loop(gui.mlx);
	return (EXIT_SUCCESS);
}
