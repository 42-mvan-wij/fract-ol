/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:39:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/26 20:37:06 by mvan-wij      ########   odam.nl         */
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
	init_fractal(&gui);
	return (gui);
}

void	init_fractal(t_gui *gui)
{
	t_fractal	f;

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

char	*gui_get_pixel_data(t_canvas *canvas, size_t x, size_t y)
{
	return (&canvas->data[y * canvas->line_len + x * canvas->bpp / 8]);
}

void	gui_set_pixel(size_t x, size_t y, t_color color, t_gui *gui)
{
	char	*pixel_data;
	int		bytes_per_pix;

	pixel_data = gui_get_pixel_data(&gui->canvas, x, y);
	if (gui->canvas.endian == 0)
	{
		pixel_data[0] = (uint8_t)color.b; // endian-ness
		pixel_data[1] = (uint8_t)color.g;
		pixel_data[2] = (uint8_t)color.r;
		return ;
	}
	bytes_per_pix = gui->canvas.bpp / 8;
	pixel_data[bytes_per_pix - 1] = (uint8_t)color.b;
	pixel_data[bytes_per_pix - 2] = (uint8_t)color.g;
	pixel_data[bytes_per_pix - 3] = (uint8_t)color.r;
}

t_color	rgb_from_hue(double hue)
{
	int		region;
	double	ff;

	region = floor(hue / 60);
	ff = remainder(hue, 60) * 6;
	if (region == 0)
		return ((t_color){255.0, ff, 0.0});
	if (region == 1)
		return ((t_color){1.0 - ff, 255.0, 0.0});
	if (region == 2)
		return ((t_color){0.0, 255.0, ff});
	if (region == 3)
		return ((t_color){0.0, 1.0 - ff, 255.0});
	if (region == 4)
		return ((t_color){ff, 0.0, 255.0});
	return ((t_color){255.0, 0.0, 1.0 - ff});
}

t_color	pallette(int i, int max_i)
{
	if (i == max_i)
		return ((t_color){0, 0, 0});
	return (rgb_from_hue(i));
}

int	main(void)
{
	t_gui	gui;

	gui = create_gui(1400, 800, "test");
	mlx_hook(gui.window, CROSS_PRESS, CROSS_PRESS_MASK, close_hook, NULL);
	mlx_hook(gui.window, KEY_PRESS, KEY_PRESS_MASK, key_hook, &gui);
	mlx_hook(gui.window, BUTTON_PRESS, BUTTON_PRESS_MASK, button_hook, &gui);
	mlx_loop_hook(gui.mlx, loop_hook, &gui);
	mlx_loop(gui.mlx);
}
