/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:38:06 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 15:06:23 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	blit_scaled_row(uint32_t *dst, t_game *g, int y)
{
	int		x;
	int		src_x;
	int		src_y;

	if (!dst || !g || !g->frame || !g->frame->pixels
		|| (unsigned int)y >= (unsigned int)g->win_height)
		return ;
	src_y = y * g->frame->height / g->win_height;
	if ((unsigned int)src_y >= g->frame->height)
		src_y = g->frame->height - 1;
	x = 0;
	while (x < g->win_width)
	{
		src_x = x * g->frame->width / g->win_width;
		if ((unsigned int)src_x >= g->frame->width)
			src_x = g->frame->width - 1;
		dst[y * g->win_width + x] = ((uint32_t *)g->frame->pixels)
		[src_y * g->frame->width + src_x];
		x++;
	}
}

void	blit_scaled(t_game *g)
{
	int			y;
	uint32_t	*dst;

	if (!g || !g->frame || !g->frame->pixels || !g->img || !g->img->pixels)
		return ;
	dst = (uint32_t *)g->img->pixels;
	y = 0;
	while (y < g->win_height)
	{
		blit_scaled_row(dst, g, y);
		y++;
	}
}
