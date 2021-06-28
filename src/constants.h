/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   constants.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 14:48:35 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/06/28 16:34:11 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

typedef struct s_canvas {
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_canvas;

typedef struct s_gui {
	void		*mlx;
	void		*window;
	t_canvas	canvas;
	int			do_redraw;
}	t_gui;

#endif
