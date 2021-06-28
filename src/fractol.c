/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:39:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/06/28 16:51:18 by mvan-wij      ########   odam.nl         */
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
	return (gui);
}

#ifdef __APPLE__
# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define BUTTON_PRESS 4
# define BUTTON_PRESS_MASK 1
# define CROSS_PRESS 17
# define CROSS_PRESS_MASK 1 << 17

# define BUTTON_LEFT 1
# define BUTTON_RIGHT 2
# define BUTTON_MIDDLE 3
# define BUTTON_SCROLL_UP 4
# define BUTTON_SCROLL_DOWN 5

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
#else
# define KEY_PRESS 2
# define KEY_PRESS_MASK 1
# define CROSS_PRESS 33
# define CROSS_PRESS_MASK 0

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
#endif

typedef struct s_color {
	double	r;
	double	g;
	double	b;
}	t_color;

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

t_color rgb_from_hue(double hue)
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
		return ((t_color){0,0,0});
	return (rgb_from_hue(i));
}

void	draw_image(t_gui *gui)
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

int	loop_hook(t_gui *gui)
{
	if (gui->do_redraw)
	{
		gui->do_redraw = 0;
		draw_image(gui);
		mlx_put_image_to_window(gui->mlx, gui->window, gui->canvas.img, 0, 0);
	}
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
		close_hook();
	else
		printf("unknown key: %i (%c)\n", keycode, keycode);
	return (0);
}

int	button_hook(int button, t_gui *gui)
{
	(void)gui;
	if (button == BUTTON_SCROLL_UP)
	{
		printf("up\n");
		// zoom_in(gui);
	}
	else if (button == BUTTON_SCROLL_DOWN)
	{
		// zoom_out(gui);;
	}
	else
		printf("unknown button: %i\n", button);
	return (0);
}

int	main(void)
{

	t_gui gui = create_gui(1400, 800, "test");
	// mlx_loop_hook(gui.mlx)
	mlx_hook(gui.window, CROSS_PRESS, CROSS_PRESS_MASK, close_hook, NULL);
	mlx_hook(gui.window, KEY_PRESS, KEY_PRESS_MASK, key_hook, &gui);
	mlx_hook(gui.window, BUTTON_PRESS, BUTTON_PRESS_MASK, button_hook, &gui);
	mlx_loop_hook(gui.mlx, loop_hook, &gui);
	mlx_loop(gui.mlx);
}
