/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   constants.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:48:35 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/26 16:04:54 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifdef __APPLE__
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 1
#  define BUTTON_PRESS 4
#  define BUTTON_PRESS_MASK 1
#  define CROSS_PRESS 17
#  define CROSS_PRESS_MASK 1 << 17

#  define BUTTON_LEFT 1
#  define BUTTON_RIGHT 2
#  define BUTTON_MIDDLE 3
#  define BUTTON_SCROLL_UP 4
#  define BUTTON_SCROLL_DOWN 5

#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 1
#  define BUTTON_PRESS 4
#  define BUTTON_PRESS_MASK 1L<<2
#  define CROSS_PRESS 33
#  define CROSS_PRESS_MASK 0

#  define BUTTON_LEFT 1
#  define BUTTON_RIGHT 3
#  define BUTTON_MIDDLE 2
#  define BUTTON_SCROLL_UP 4
#  define BUTTON_SCROLL_DOWN 5
// #  define BUTTON_FORWARD 9
// #  define BUTTON_BACKWARD 8

#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
# endif

typedef struct s_color {
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_canvas {
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_canvas;

typedef struct s_fractal {
	double	zoom;
	double	x_pos;
	double	y_pos;
	double	scalar;
	double	from_x;
	double	from_y;
	double	to_x;
	double	to_y;
	double	x_size;
	double	y_size;
}	t_fractal;

typedef struct s_gui {
	void		*mlx;
	void		*window;
	t_canvas	canvas;
	int			do_redraw;
	int			is_redrawing;
	t_fractal	fractal;
	// double		zoom;
	// double		x_pos;
	// double		y_pos;
	// double		scalar;
	// double		from_x;
	// double		from_y;
	// double		to_x;
	// double		to_y;
	// double		x_size;
	// double		y_size;
}	t_gui;

#endif
