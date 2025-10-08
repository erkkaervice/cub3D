/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:18:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 19:14:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bitmap_pixel(t_game *g, t_point pos, int scale, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			hud_blend((t_hud){(uint32_t *)g->frame->pixels,
				g->frame->width, g->frame->height,
				pos.x + x, pos.y + y, color, 0.5f});
			x++;
		}
		y++;
	}
}

static const char	**bitmap_digits(void)
{
	static const char	*digits[FONT_DIGITS] = {
		"\x07\x05\x05\x05\x07",
		"\x02\x06\x02\x02\x07",
		"\x07\x01\x07\x04\x07",
		"\x07\x01\x07\x01\x07",
		"\x05\x05\x07\x01\x01",
		"\x07\x04\x07\x01\x07",
		"\x07\x04\x07\x05\x07",
		"\x07\x01\x02\x02\x02",
		"\x07\x05\x07\x05\x07",
		"\x07\x05\x07\x01\x07"
	};

	return (digits);
}

static const char	**bitmap_letters(void)
{
	static const char	*letters[FONT_LETTERS] = {
		"\x07\x04\x07\x04\x04",
		"\x07\x05\x07\x04\x04",
		"\x07\x04\x07\x01\x07"
	};

	return (letters);
}

static void	bitmap_draw(t_game *g, t_point pos,
	const char bmap[FONT_ROWS], int scale)
{
	int	r;
	int	c;

	r = 0;
	while (r < FONT_ROWS)
	{
		c = 0;
		while (c < FONT_COLS)
		{
			if (bmap[r] & (1 << (FONT_COLS - 1 - c)))
				bitmap_pixel(g, (t_point){pos.x + c * scale,
					pos.y + r * scale}, scale, FPS_COLOR);
			c++;
		}
		r++;
	}
}

void	bitmap_char(t_game *g, t_point pos, char c, int scale)
{
	const char	**d = bitmap_digits();
	const char	**l = bitmap_letters();

	if (c >= '0' && c <= '9')
		bitmap_draw(g, pos, d[c - '0'], scale);
	else if (c == 'F')
		bitmap_draw(g, pos, l[0], scale);
	else if (c == 'P')
		bitmap_draw(g, pos, l[1], scale);
	else if (c == 'S')
		bitmap_draw(g, pos, l[2], scale);
	else if (c == ':')
	{
		bitmap_pixel(g, (t_point){pos.x + scale, pos.y + COLON_TOP * scale},
			scale, FPS_COLOR);
		bitmap_pixel(g, (t_point){pos.x + scale, pos.y + COLON_BOTTOM * scale},
			scale, FPS_COLOR);
	}
}
