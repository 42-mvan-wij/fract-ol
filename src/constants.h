/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   constants.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:48:35 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/15 12:50:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifdef BONUS
#  define ZOOM_AT_MOUSE 1
# else
#  define ZOOM_AT_MOUSE 0
# endif

# ifdef __APPLE__
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 1
#  define BUTTON_PRESS 4
#  define BUTTON_PRESS_MASK 1
#  define CROSS_PRESS 17
#  define CROSS_PRESS_MASK 131072L
//                         1L << 17

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
#  define KEY_SPACE 49
#  define KEY_UP 126
#  define KEY_LEFT 123
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
# else
#  define KEY_PRESS 2
#  define KEY_PRESS_MASK 1
#  define BUTTON_PRESS 4
#  define BUTTON_PRESS_MASK 4L
//                          1L << 2
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
#  define KEY_UP 65362
#  define KEY_SPACE 32
#  define KEY_LEFT 65361
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
# endif

typedef struct s_color {
	long double	r;
	long double	g;
	long double	b;
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

typedef enum e_fractal_type {
	MANDELBROT,
	JULIA,
	MULTIBROT,
	JULIA_ANIM
}	t_fractal_type;

typedef struct s_fractal {
	long double		zoom;
	long double		x_pos;
	long double		y_pos;
	long double		scalar;
	long double		from_x;
	long double		from_y;
	long double		to_x;
	long double		to_y;
	long double		x_size;
	long double		y_size;
	int				max_it;
	t_fractal_type	e_type;
	union {
		struct {
			long double	c_re;
			long double	c_im;
		};
		struct {
			long double	exp;
		};
	}		u_vars;
}	t_fractal;

typedef struct s_gui {
	void		*mlx;
	void		*window;
	t_canvas	canvas;
	int			do_redraw;
	int			is_redrawing;
	t_fractal	fractal;
}	t_gui;

#endif
