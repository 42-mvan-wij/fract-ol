/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defs.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 16:35:22 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 15:43:31 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <stddef.h>
# include "constants.h"

t_canvas	create_canvas(t_gui *gui, int width, int height);
t_gui		create_gui(int width, int height, char *title);
int			zoom(t_gui *gui, double amount);
int			move(t_gui *gui, double x_amount, double y_amount);
int			loop_hook(t_gui *gui);
int			close_hook(void);
int			key_hook(int keycode, t_gui *gui);
int			button_hook(int button, int _, int _2, t_gui *gui);
void		draw_mandelbrot(t_gui *gui, double x, double y, double zoom);
void		draw_julia(t_gui *gui, double x, double y, double zoom);
void		draw_multibrot(t_gui *gui, double x, double y, double zoom);
void		init_fractal(t_gui *gui);
int			init_mandelbrot_set(t_gui *gui, char *args[], int argc);
int			init_julia_set(t_gui *gui, char *args[], int argc);
int			init_multibrot_set(t_gui *gui, char *args[], int argc);
void		draw_fractal(t_gui *gui);
char		*gui_get_pixel_data(t_canvas *canvas, size_t x, size_t y);
void		gui_set_pixel(size_t x, size_t y, t_color color, t_gui *gui);
t_color		pallette(int i, int max_i);
void		draw_fractal_bonus(t_gui *gui);
int			parse_args_bonus(char *argv[], int argc, t_gui *gui);

#endif
