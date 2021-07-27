/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 11:18:45 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/26 21:18:24 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "defs.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

// #ifdef BONUS
# include "bonus.h"
// #endif

int	loop_hook(t_gui *gui)
{
	if (gui->do_redraw && !gui->is_redrawing)
	{
		gui->is_redrawing = 1;
		gui->do_redraw = 0;
		printf("will redraw\n");
		// draw_multibrot(gui, gui->fractal.x_pos, gui->fractal.y_pos, 0.6, gui->fractal.zoom, 1024);
		draw_multibrot(gui, gui->fractal.x_pos, gui->fractal.y_pos, -2, gui->fractal.zoom, 128);
		// draw_julia(gui, -0.8, 0.156, gui->fractal.x_pos, gui->fractal.y_pos, gui->fractal.zoom, 1024);
		// draw_julia(gui, -0.8, 0.156, gui->fractal.x_pos, gui->fractal.y_pos, gui->fractal.zoom, 128);
		// draw_mandelbrot(gui, gui->fractal.x_pos, gui->fractal.y_pos, gui->fractal.zoom, 1024);
		// draw_mandelbrot(gui, gui->fractal.x_pos, gui->fractal.y_pos, gui->fractal.zoom, 128);
		mlx_put_image_to_window(gui->mlx, gui->window, gui->canvas.img, 0, 0);
		printf("did redraw\n");
		gui->is_redrawing = 0;
		// t_complex z = {-0.35, 1.3};
		// t_complex a = complex_pow(z, 0.6);
		// printf("ye: %lf, %lf\n", a.re, a.im);
		// z.im *= -1;
		// a = complex_pow(z, 0.6);
		// printf("ne: %lf, %lf\n", a.re, a.im);
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
	if (button == BUTTON_SCROLL_UP)
		return (zoom(gui, 1.1));
	if (button == BUTTON_SCROLL_DOWN)
		return (zoom(gui, 1 / 1.1));
	else
		printf("unknown button: %i\n", button);
	return (0);
}
