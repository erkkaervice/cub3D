/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:26:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 17:58:45 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define CHAR_COLOR	0xFFFFFF

static const char	(*get_font_digits(void))[5]
{
	static const char	font_digits[10][5] = {
	{7, 5, 5, 5, 7},
	{2, 6, 2, 2, 7},
	{7, 1, 7, 4, 7},
	{7, 1, 7, 1, 7},
	{5, 5, 7, 1, 1},
	{7, 4, 7, 1, 7},
	{7, 4, 7, 5, 7},
	{7, 1, 2, 2, 2},
	{7, 5, 7, 5, 7},
	{7, 5, 7, 1, 7}
	};

	return (font_digits);
}

static const char	(*get_font_letters(void))[5]
{
	static const char	font_letters[3][5] = {
	{7, 4, 7, 4, 4},
	{7, 5, 7, 4, 4},
	{7, 4, 7, 1, 7}
	};

	return (font_letters);
}

static void	draw_fps_pixel(t_game *game, int x, int y, int color)
{
	uint32_t	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (uint32_t *)game->img->pixels + y * WIDTH + x;
	*pixel = color;
}

static void	draw_scaled_pixel(t_game *game, struct s_point pos,
	int scale, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < scale)
	{
		dx = 0;
		while (dx < scale)
		{
			draw_fps_pixel(game, pos.x + dx, pos.y + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	draw_char(t_game *game, struct s_point pos,
	const char bitmap[5], int scale)
{
	int	row;
	int	col;

	row = 0;
	while (row < 5)
	{
		col = 0;
		while (col < 3)
		{
			if (bitmap[row] & (1 << (2 - col)))
				draw_scaled_pixel(game, (struct s_point){pos.x + col
					* scale, pos.y + row * scale}, scale, CHAR_COLOR);
			col++;
		}
		row++;
	}
}

static void	setup_fonts(const char **digits_arr, const char **letters_arr)
{
	int	i;

	i = 0;
	while (i < 10)
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
	static const char	*digits_arr[10];
	static const char	*letters_arr[3];
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
			scale, CHAR_COLOR);
		draw_scaled_pixel(game, (struct s_point){pos.x + scale, pos.y
			+ 3 * scale},
			scale, CHAR_COLOR);
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
		x += (3 * scale) + scale;
		i++;
		c = str[i];
	}
}

void	update_fps(t_fps *fps)
{
	clock_t	now;

	fps->frames++;
	now = clock();
	if ((now - fps->last_time) >= CLOCKS_PER_SEC)
	{
		fps->fps = fps->frames;
		fps->frames = 0;
		fps->last_time = now;
	}
}

static void	draw_fps_text(t_game *game)
{
	int		scale;
	int		x;
	int		y;
	char	*str;

	scale = 5;
	x = WIDTH - 100 - 60 + 5;
	y = 10 + (20 - 5 * scale) / 2;
	draw_string(game, (struct s_point){x, y}, "FPS:", scale);
	str = ft_itoa(game->fps.fps);
	if (str)
	{
		draw_string(game, (struct s_point){x + 4 * (3 * scale + scale), y},
			str, scale);
		free(str);
	}
}

void	render_fps(t_game *game)
{
	if (!game->fps_visible)
		return ;
	update_fps(&game->fps);
	draw_fps_text(game);
}
