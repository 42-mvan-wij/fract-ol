/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 15:38:33 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/07/28 15:44:58 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "defs.h"
#include "libft.h"

#ifdef BONUS

void	draw_fractal_bonus(t_gui *gui)
{
	if (gui->fractal.e_type == MULTIBROT)
		draw_multibrot(gui, gui->fractal.x_pos, gui->fractal.y_pos,
			gui->fractal.zoom);
}

int	parse_args_bonus(char *argv[], int argc, t_gui *gui)
{
	if (ft_strncmp(argv[1], "multibrot", 9) == 0)
	{
		if (argc < 3)
			return (0);
		*gui = create_gui(1500, 800, "Multibrot set");
		return (init_multibrot_set(gui, &argv[2], argc - 2));
	}
	return (0);
}

#else

void	draw_fractal_bonus(t_gui *gui)
{
	(void)gui;
}

int	parse_args_bonus(char *argv[], int argc, t_gui *gui)
{
	(void)argv;
	(void)argc;
	(void)gui;
	return (0);
}

#endif
