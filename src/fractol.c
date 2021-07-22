/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:39:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/22 18:10:04 by mvan-wij      ########   odam.nl         */
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
	gui.zoom = 1;
	gui.x_pos = -0.75;
	gui.y_pos = 0;
	return (gui);
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

/*void	draw_image(t_gui *gui)
{
	const double	x_scalar = 3.5 / gui->canvas.width;
	const double	y_scalar = 2.0 / gui->canvas.height;





	int	px;
	int	py;
	double	x0;
	double	y0;

	double	x;
	double	y;
	double	x2;
	double	y2;
	int		i;
	const int	max_i = 1024;
	t_color	color;

	py = 0;
	while (py < gui->canvas.height)
	{
		y0 = (double)py * fmax(x_scalar, y_scalar) - 1;
		px = 0;
		while (px < gui->canvas.width)
		{
			x0 = (double)px * fmax(x_scalar, y_scalar) - 2.5;


			x = 0;
			y = 0;

			x2 = 0;
			y2 = 0;

			i = 0;
			while (x2 + y2 <= 4 && i < max_i)
			{
				y = 2 * x * y + y0;
				x = x2 - y2 + x0;
				x2 = x * x;
				y2 = y * y;
				i++;
			}
			color = pallette(i, max_i);
			gui_set_pixel(px, py, color, gui);


			px++;
		}
		py++;
	}
}
*/

void	get_mouse_coords(t_gui *gui, double *x_out, double *y_out)
{
	const double	scalar = fmax(3.5 / gui->canvas.width, 2.0 / gui->canvas.height);
	int				x;
	int				y;

	mlx_mouse_get_pos(gui->mlx, gui->window, &x, &y);
	*x_out = gui->x_pos + (((double)x * scalar) - 1.75) * gui->zoom;
	*y_out = gui->y_pos + (((double)y * scalar) - 1.0) * gui->zoom;
}

int	loop_hook(t_gui *gui)
{
	if (gui->do_redraw && !gui->is_redrawing)
	{
		gui->is_redrawing = 1;
		gui->do_redraw = 0;
		printf("will redraw\n");
		// draw_image(gui);
		draw_mandelbrot(gui, gui->x_pos, gui->y_pos, gui->zoom, 1024);
		// draw_mandelbrot(gui, gui->x_pos, gui->y_pos, gui->zoom, 128);
		mlx_put_image_to_window(gui->mlx, gui->window, gui->canvas.img, 0, 0);
		printf("did redraw\n");
		gui->is_redrawing = 0;
	}
	// double x, y;
	// get_mouse_coords(gui, &x, &y);
	// printf("x: %lf, y: %lf\t", x, y);
	// int x0, y0;
	// mlx_mouse_get_pos(gui->mlx, gui->window, &x0, &y0);
	// printf("x0: %i, y0: %i\n", x0, y0);
	return (0);
}

int	zoom(t_gui *gui, double amount)
{
	printf("zoom\n");
	gui->zoom /= amount;
	gui->do_redraw = 1;
	return (0);
}

int	move(t_gui *gui, double x_amount, double y_amount)
{
	printf("move\n");
	gui->x_pos += x_amount * gui->zoom;
	gui->y_pos += y_amount * gui->zoom;
	gui->do_redraw = 1;
	return (0);
}

int	close_hook(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_gui *gui)
{
	(void)gui;
	if (keycode == KEY_ESC)
		return (close_hook());
	if (keycode == KEY_W)
		return (zoom(gui, 1.1));
	if (keycode == KEY_S)
		return (zoom(gui, 1.0 / 1.1));
	if (keycode == KEY_A)
		return (zoom(gui, 3.0));
	if (keycode == KEY_D)
		return (zoom(gui, 1.0 / 3.0));
	if (keycode == KEY_UP)
		return (move(gui, 0, -0.1));
	if (keycode == KEY_DOWN)
		return (move(gui, 0, 0.1));
	if (keycode == KEY_LEFT)
		return (move(gui, -0.1, 0));
	if (keycode == KEY_RIGHT)
		return (move(gui, 0.1, 0));
	printf("unknown key: %i (%c)\n", keycode, keycode);
	return (0);
}

int	button_hook(int button, int _, int _2, t_gui *gui)
{
	(void)_, (void)_2;
	printf("button: %i, gui: %p\n", button, gui);
	(void)gui;
	if (button == BUTTON_SCROLL_UP)
		return (zoom(gui, 1.1));
		// return (0);
	if (button == BUTTON_SCROLL_DOWN)
		return (zoom(gui, 1 / 1.1));
		// return (0);
	else
		printf("unknown button: %i\n", button);
	return (0);
}

int	main(void)
{
	t_gui	gui;
	printf("gui: %p\n", &gui);

	gui = create_gui(1400, 800, "test");
	mlx_hook(gui.window, CROSS_PRESS, CROSS_PRESS_MASK, close_hook, NULL);
	mlx_hook(gui.window, KEY_PRESS, KEY_PRESS_MASK, key_hook, &gui);
	mlx_hook(gui.window, BUTTON_PRESS, BUTTON_PRESS_MASK, button_hook, &gui);
	mlx_loop_hook(gui.mlx, loop_hook, &gui);
	mlx_loop(gui.mlx);
}
