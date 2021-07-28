/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 14:13:09 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 14:14:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include <stddef.h>
#include <stdint.h>
#include <math.h>

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
		pixel_data[0] = (uint8_t)color.b;
		pixel_data[1] = (uint8_t)color.g;
		pixel_data[2] = (uint8_t)color.r;
		return ;
	}
	bytes_per_pix = gui->canvas.bpp / 8;
	pixel_data[bytes_per_pix - 1] = (uint8_t)color.b;
	pixel_data[bytes_per_pix - 2] = (uint8_t)color.g;
	pixel_data[bytes_per_pix - 3] = (uint8_t)color.r;
}

static t_color	rgb_from_hue(double hue)
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
