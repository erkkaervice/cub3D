/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:26:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 16:10:21 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define CHAR_COLOR	0xFFFFFF

static const char	g_font_digits[10][5] = {
	{7,5,5,5,7},
	{2,6,2,2,7},
	{7,1,7,4,7},
	{7,1,7,1,7},
	{5,5,7,1,1},
	{7,4,7,1,7},
	{7,4,7,5,7},
	{7,1,2,2,2},
	{7,5,7,5,7},
	{7,5,7,1,7}
};

static const char	g_font_letters[3][5] = {
	{7,4,7,4,4},
	{7,5,7,4,4},
	{7,4,7,1,7}
};

static void	draw_fps_pixel(t_game *game, int x, int y, int color)
{
	uint32_t	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (uint32_t *)game->img->pixels + y * WIDTH + x;
	*pixel = color;
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

static void	draw_scaled_pixel(t_game *game, int x, int y, int scale, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < scale)
	{
		dx = 0;
		while (dx < scale)
		{
			draw_fps_pixel(game, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	draw_char(t_game *game, int x, int y, const char bitmap[5],
		int scale)
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
				draw_scaled_pixel(game,
					x + col * scale,
					y + row * scale,
					scale,
					CHAR_COLOR);
			col++;
		}
		row++;
	}
}

static void	draw_string(t_game *game, int x, int y, const char *str, int scale)
{
	int		i;
	int		pos_x;
	char	c;

	pos_x = x;
	i = 0;
	while ((c = str[i]))
	{
		if (c >= '0' && c <= '9')
			draw_char(game, pos_x, y, g_font_digits[c - '0'], scale);
		else if (c == 'F')
			draw_char(game, pos_x, y, g_font_letters[0], scale);
		else if (c == 'P')
			draw_char(game, pos_x, y, g_font_letters[1], scale);
		else if (c == 'S')
			draw_char(game, pos_x, y, g_font_letters[2], scale);
		else if (c == ':')
		{
			draw_scaled_pixel(game, pos_x + scale, y + scale, scale, CHAR_COLOR);
			draw_scaled_pixel(game, pos_x + scale, y + 3 * scale, scale,
				CHAR_COLOR);
		}
		pos_x += (3 * scale) + scale;
		i++;
	}
}

static void	draw_fps_text(t_game *game)
{
	int		scale;
	int		box_w;
	int		box_h;
	int		char_h;
	int		x;
	int		y;
	char	*str;

	scale = 5;
	box_w = 100;
	box_h = 20;
	char_h = 5 * scale;
	x = WIDTH - box_w - 60 + 5;
	y = 10 + (box_h - char_h) / 2;
	draw_string(game, x, y, "FPS:", scale);
	str = ft_itoa(game->fps.fps);
	if (str)
	{
		draw_string(game, x + 4 * ((3 * scale) + scale), y, str, scale);
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
