/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:38:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 16:37:41 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	blit_scaled_row(uint32_t *dst, t_game *game, float *scale, int y)
{
	int	x;

	x = 0;
	scale[2] = 0;
	while (x < game->win_width)
	{
		dst[y * game->win_width + x]
			= ((uint32_t *)game->frame->pixels)
		[(int)scale[3] * game->win_width + (int)scale[2]];
		scale[2] += scale[0];
		x++;
	}
}

void	blit_scaled(t_game *game)
{
	int			y;
	uint32_t	*dst;
	float		scale[4];

	if (!game->frame || !game->img)
		return ;
	scale[0] = (float)game->frame->width / (float)game->win_width;
	scale[1] = (float)game->frame->height / (float)game->win_height;
	dst = (uint32_t *)game->img->pixels;
	y = 0;
	scale[3] = 0;
	while (y < game->win_height)
	{
		blit_scaled_row(dst, game, scale, y);
		scale[3] += scale[1];
		y++;
	}
}
