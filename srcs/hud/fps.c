/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:26:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 18:09:16 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_fonts(const char **digits_arr, const char **letters_arr)
{
	int	i;

	i = 0;
	while (i < FONT_DIGITS_COUNT)
	{
		digits_arr[i] = get_font_digits()[i];
		i++;
	}
	letters_arr[0] = get_font_letters()[0];
	letters_arr[1] = get_font_letters()[1];
	letters_arr[2] = get_font_letters()[2];
}

static void	draw_string_char(t_game *game,
	struct s_point pos, char c, int scale)
{
	static const char	*digits_arr[FONT_DIGITS_COUNT];
	static const char	*letters_arr[FONT_LETTERS_COUNT];
	static int			init = 0;

	if (!init)
	{
		setup_fonts(digits_arr, letters_arr);
		init = 1;
	}
	if (c >= '0' && c <= '9')
		draw_char(game, pos, digits_arr[c - '0'], scale);
	else if (c == 'F')
		draw_char(game, pos, letters_arr[0], scale);
	else if (c == 'P')
		draw_char(game, pos, letters_arr[1], scale);
	else if (c == 'S')
		draw_char(game, pos, letters_arr[2], scale);
	else if (c == ':')
	{
		draw_scaled_pixel(game, (struct s_point){pos.x + scale, pos.y + scale},
			scale, FPS_CHAR_COLOR);
		draw_scaled_pixel(game, (struct s_point){pos.x + scale, pos.y
			+ 3 * scale}, scale, FPS_CHAR_COLOR);
	}
}

static void	draw_string(t_game *game, struct s_point pos,
	const char *str, int scale)
{
	int		i;
	int		x;
	char	c;

	x = pos.x;
	i = 0;
	c = str[i];
	while (c != '\0')
	{
		draw_string_char(game, (struct s_point){x, pos.y}, c, scale);
		x += FPS_CHAR_SPACING;
		i++;
		c = str[i];
	}
}

static void	draw_fps_text(t_game *game)
{
	char	*str;
	int		text_width;
	int		label_x;
	int		value_x;

	text_width = FPS_CHAR_SPACING * (int)ft_strlen(FPS_LABEL);
	text_width += FPS_CHAR_SPACING * 3;
	label_x = WINDOW_WIDTH - text_width - 8;
	value_x = WINDOW_WIDTH - FPS_CHAR_SPACING * 3 - 8;
	draw_string(game, (struct s_point){label_x, FPS_POS_Y},
		FPS_LABEL, FPS_SCALE);
	str = ft_itoa(game->fps.fps);
	if (str)
	{
		draw_string(game, (struct s_point){value_x, FPS_POS_Y},
			str, FPS_SCALE);
		free(str);
	}
}

void	render_fps(t_game *game)
{
	clock_t	now;

	if (!game->fps_visible)
		return ;
	game->fps.frames++;
	now = clock();
	if ((now - game->fps.last_time) >= CLOCKS_PER_SEC)
	{
		game->fps.fps = game->fps.frames;
		game->fps.frames = 0;
		game->fps.last_time = now;
	}
	draw_fps_text(game);
}
