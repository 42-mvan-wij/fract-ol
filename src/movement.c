/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 15:39:44 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/26 16:07:18 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

int	zoom(t_gui *gui, double amount)
{
	double	x;
	double	y;
	int		mx;
	int		my;

	printf("zoom\n");
	mlx_mouse_get_pos(gui->mlx, gui->window, &mx, &my);
	if (mx >= 0 && mx < gui->canvas.width && my >= 0 && my < gui->canvas.height)
	{
		x = gui->fractal.x_pos + ((mx * gui->fractal.scalar) - gui->fractal.x_size / 2) * gui->fractal.zoom;
		y = gui->fractal.y_pos + ((my * gui->fractal.scalar) - gui->fractal.y_size / 2) * gui->fractal.zoom;
		gui->fractal.x_pos += (x - gui->fractal.x_pos) * (1 - 1 / amount);
		gui->fractal.y_pos += (y - gui->fractal.y_pos) * (1 - 1 / amount);
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
