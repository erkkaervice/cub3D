/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:50:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 20:06:21 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fps_pixel(t_game *game, int x, int y, int color)
{
	uint32_t	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = (uint32_t *)game->img->pixels + y * WIDTH + x;
	*pixel = color;
}

void	draw_scaled_pixel(t_game *game, struct s_point pos,
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

void	draw_char(t_game *game, struct s_point pos,
	const char bmap[5], int scale)
{
	int	row;
	int	col;

	row = 0;
	while (row < 5)
	{
		col = 0;
		while (col < 3)
		{
			if (bmap[row] & (1 << (2 - col)))
				draw_scaled_pixel(game, (struct s_point){pos.x + col
					* scale, pos.y + row * scale}, scale, CHAR_COLOR);
			col++;
		}
		row++;
	}
}

const char	**get_font_digits(void)
{
	static const char	*font_digits[10] = {
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
	static const char	*font_letters[3] = {
		(char *)"\x07\x04\x07\x04\x04",
		(char *)"\x07\x05\x07\x04\x04",
		(char *)"\x07\x04\x07\x01\x07"
	};

	return (font_letters);
}
