/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 15:39:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 16:17:22 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

#ifdef __APPLE__

static int	get_mouse_pos(t_gui *gui, int *x, int *y)
{
	const int	ret = mlx_mouse_get_pos(gui->window, x, y);

	*y -= 20;
	return (ret);
}

#else

static int	get_mouse_pos(t_gui *gui, int *x, int *y)
{
	return (mlx_mouse_get_pos(gui->mlx, gui->window, x, y));
}

#endif

int	zoom(t_gui *gui, double amount)
{
	double	x;
	double	y;
	int		mx;
	int		my;

	printf("zoom\n");
	if (ZOOM_AT_MOUSE)
	{
		get_mouse_pos(gui, &mx, &my);
		if (mx >= 0 && mx < gui->canvas.width
			&& my >= 0 && my < gui->canvas.height)
		{
			x = gui->fractal.x_pos + gui->fractal.scalar * gui->fractal.zoom
				* (mx - gui->canvas.width / 2);
			y = gui->fractal.y_pos + gui->fractal.scalar * gui->fractal.zoom
				* (my - gui->canvas.height / 2);
			gui->fractal.x_pos += (x - gui->fractal.x_pos) * (1 - 1 / amount);
			gui->fractal.y_pos += (y - gui->fractal.y_pos) * (1 - 1 / amount);
		}
	}
	gui->fractal.zoom /= amount;
	gui->do_redraw = 1;
	return (0);
}

int	move(t_gui *gui, double x_amount, double y_amount)
{
	printf("move\n");
	gui->fractal.x_pos += x_amount * gui->fractal.zoom;
	gui->fractal.y_pos += y_amount * gui->fractal.zoom;
	gui->do_redraw = 1;
	return (0);
}
