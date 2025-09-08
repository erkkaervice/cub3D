/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:50:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/08 17:14:57 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fps_pixel(t_game *g, int win_x, int win_y, int color)
{
	int			frame_x;
	int			frame_y;
	uint32_t	*pixel;

	if (!g || !g->frame || !g->frame->pixels)
		return ;
	frame_x = win_x * g->frame->width / g->win_width;
	frame_y = win_y * g->frame->height / g->win_height;
	if (frame_x < 0 || frame_x >= (int)g->frame->width
		|| frame_y < 0 || frame_y >= (int)g->frame->height)
		return ;
	pixel = (uint32_t *)g->frame->pixels + frame_y * g->frame->width + frame_x;
	*pixel = color;
}

void	draw_scaled_pixel(t_game *g, struct s_point pos, int scale, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < scale)
	{
		dx = 0;
		while (dx < scale)
		{
			draw_fps_pixel(g, pos.x + dx, pos.y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_char(t_game *g, struct s_point pos,
	const char bmap[FONT_ROWS], int scale)
{
	int	row;
	int	col;

	row = 0;
	while (row < FONT_ROWS)
	{
		col = 0;
		while (col < FONT_COLS)
		{
			if (bmap[row] & (1 << (FONT_COLS - 1 - col)))
				draw_scaled_pixel(g, (struct s_point)
				{pos.x + col * scale, pos.y + row * scale},
					scale, FPS_CHAR_COLOR);
			col++;
		}
		row++;
	}
}

const char	**get_font_digits(void)
{
	static const char	*font_digits[FONT_DIGITS_COUNT] = {
		(char *)"\x07\x05\x05\x05\x07",
		(char *)"\x02\x06\x02\x02\x07",
		(char *)"\x07\x01\x07\x04\x07",
		(char *)"\x07\x01\x07\x01\x07",
		(char *)"\x05\x05\x07\x01\x01",
		(char *)"\x07\x04\x07\x01\x07",
		(char *)"\x07\x04\x07\x05\x07",
		(char *)"\x07\x01\x02\x02\x02",
		(char *)"\x07\x05\x07\x05\x07",
		(char *)"\x07\x05\x07\x01\x07"
	};

	return (font_digits);
}

const char	**get_font_letters(void)
{
	static const char	*font_letters[FONT_LETTERS_COUNT] = {
		(char *)"\x07\x04\x07\x04\x04",
		(char *)"\x07\x05\x07\x04\x04",
		(char *)"\x07\x04\x07\x01\x07"
	};

	return (font_letters);
}
