/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:39:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 14:21:32 by mvan-wij      ########   odam.nl         */
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

t_canvas	create_canvas(t_gui *gui, int width, int height)
{
	t_canvas	canvas;

	canvas.img = mlx_new_image(gui->mlx, width, height);
	canvas.width = width;
	canvas.height = height;
	canvas.data = mlx_get_data_addr(canvas.img, &canvas.bpp, &canvas.line_len,
			&canvas.endian);
	return (canvas);
}

t_gui	create_gui(int width, int height, char *title)
{
	t_gui	gui;

	gui.mlx = mlx_init();
	gui.canvas = create_canvas(&gui, width, height);
	gui.window = mlx_new_window(gui.mlx, width, height, title);
	gui.do_redraw = 1;
	gui.is_redrawing = 0;
	return (gui);
}

int	parse_args(char *argv[], int argc, t_gui *gui)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
	{
		*gui = create_gui(1400, 800, "Mandelbrot set");
		return (init_mandelbrot_set(gui, &argv[2], argc - 2));
	}
	else if (ft_strncmp(argv[1], "julia", 5) == 0)
	{
		if (argc < 4)
			return (0);
		*gui = create_gui(1200, 900, "Julia set");
		return (init_julia_set(gui, &argv[2], argc - 2));
	}
	else if (BONUS_V && ft_strncmp(argv[1], "multibrot", 9) == 0)
	{
		if (argc < 3)
			return (0);
		*gui = create_gui(1500, 800, "Multibrot set");
		return (init_multibrot_set(gui, &argv[2], argc - 2));
	}
	return (0);
}

void	draw_fractal(t_gui *gui)
{
	if (gui->fractal.e_type == MANDELBROT)
		draw_mandelbrot(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
	else if (gui->fractal.e_type == JULIA)
		draw_julia(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
	else if (BONUS_V && gui->fractal.e_type == MULTIBROT)
		draw_multibrot(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
}

int	main(int argc, char *argv[])
{
	t_gui	gui;

	if (!parse_args(argv, argc, &gui))
	{
		if (BONUS_V)
		{
			printf("usage: \
%s <mandelbrot | julia | multibrot> <fractal arguments> [max iterations]\n\
Fractal arguments:\n\
\tMandelbrot Set: -\n\
\tJulia Set: <real> <imaginary>\n\
\tMultibrot Set: <exponent>\n", argv[0]);
		}
		else
		{
			printf("usage: \
%s <mandelbrot | julia> <fractal arguments> [max iterations]\n\
Fractal arguments:\n\
\tMandelbrot Set: -\n\
\tJulia Set: <real> <imaginary>\n", argv[0]);
		}
		return (EXIT_FAILURE);
	}
	mlx_hook(gui.window, CROSS_PRESS, CROSS_PRESS_MASK, close_hook, NULL);
	mlx_hook(gui.window, KEY_PRESS, KEY_PRESS_MASK, key_hook, &gui);
	mlx_hook(gui.window, BUTTON_PRESS, BUTTON_PRESS_MASK, button_hook, &gui);
	mlx_loop_hook(gui.mlx, loop_hook, &gui);
	mlx_loop(gui.mlx);
	return (EXIT_SUCCESS);
}
