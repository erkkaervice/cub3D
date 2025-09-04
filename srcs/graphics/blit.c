/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:38:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:19:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	blit_scaled_row(uint32_t *dst, t_game *g, float *scale, int y)
{
	int	x;

	x = 0;
	scale[2] = 0;
	while (x < g->win_width)
	{
		dst[y * g->win_width + x]
			= ((uint32_t *)g->frame->pixels)
		[(int)scale[3] * g->win_width + (int)scale[2]];
		scale[2] += scale[0];
		x++;
	}
}

void	blit_scaled(t_game *g)
{
	int			y;
	uint32_t	*dst;
	float		scale[4];

	if (!g->frame || !g->img)
		return ;
	scale[0] = (float)g->frame->width / (float)g->win_width;
	scale[1] = (float)g->frame->height / (float)g->win_height;
	dst = (uint32_t *)g->img->pixels;
	y = 0;
	scale[3] = 0;
	while (y < g->win_height)
	{
		blit_scaled_row(dst, g, scale, y);
		scale[3] += scale[1];
		y++;
	}
}
