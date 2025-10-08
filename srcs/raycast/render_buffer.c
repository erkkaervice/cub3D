/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:22:40 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_buffers(int32_t w, int32_t h, void *param)
{
	t_game	*game;
	float	*new_zbuf;

	game = (t_game *)param;
	if (w <= 0 || h <= 0)
		return ;
	game->win_width = w;
	game->win_height = h;
	if (game->front_buffer)
		mlx_delete_image(game->mlx, game->front_buffer);
	if (game->back_buffer)
		mlx_delete_image(game->mlx, game->back_buffer);
	game->front_buffer = mlx_new_image(game->mlx, w, h);
	game->back_buffer = mlx_new_image(game->mlx, w, h);
	if (!game->front_buffer || !game->back_buffer
		|| mlx_image_to_window(game->mlx, game->front_buffer, 0, 0) < 0)
		exit(1);
	new_zbuf = ft_calloc(w, sizeof(float));
	if (!new_zbuf)
		exit(1);
	free(game->z_buffer);
	game->z_buffer = new_zbuf;
	game->frame = game->front_buffer;
	game->needs_blit = 1;
}

void	blit_row(uint32_t *dst, uint32_t const *src,
	unsigned int y, t_game *g)
{
	unsigned int	x;
	unsigned int	src_x;
	unsigned int	src_y;
	int				min_x;
	int				max_x;

	min_x = 0;
	max_x = g->win_width - 1;
	src_y = y * g->back_buffer->height / g->win_height;
	if (src_y >= g->back_buffer->height)
		src_y = g->back_buffer->height - 1;
	x = min_x;
	while (x <= (unsigned int)max_x)
	{
		src_x = x * g->back_buffer->width / g->win_width;
		if (src_x >= g->back_buffer->width)
			src_x = g->back_buffer->width - 1;
		dst[y * g->win_width + x] = src[src_y * g->back_buffer->width + src_x];
		x++;
	}
}

void	blit_scaled(t_game *g, int min_x, int max_x)
{
	unsigned int	y;
	uint32_t		*dst;
	uint32_t const	*src;

	if (!g || !g->frame || !g->frame->pixels
		|| !g->back_buffer || !g->back_buffer->pixels)
		return ;
	if (min_x < 0)
		min_x = 0;
	if (max_x >= (int)g->win_width)
		max_x = g->win_width - 1;
	dst = (uint32_t *)g->frame->pixels;
	src = (uint32_t const *)g->back_buffer->pixels;
	y = 0;
	while (y < (unsigned int)g->win_height)
	{
		blit_row(dst, src, y, g);
		y++;
	}
}

void	copy_back(t_game *g)
{
	size_t	bytes;

	if (!g || !g->front_buffer || !g->back_buffer)
		return ;
	bytes = (size_t)g->back_buffer->width * (size_t)g->back_buffer->height
		* BYTES_PER_PIXEL;
	ft_memcpy(g->front_buffer->pixels, g->back_buffer->pixels, bytes);
}

void	blend(uint32_t *restrict dst, uint32_t src, float *restrict zbuf,
	float dist)
{
	uint32_t	dstc;
	uint8_t		a;
	uint8_t		rgb[3];

	a = (src >> 24) & 0xFF;
	if (a == 0)
		return ;
	rgb[2] = (src >> 16) & 0xFF;
	rgb[1] = (src >> 8) & 0xFF;
	rgb[0] = src & 0xFF;
	if (a == 255)
	{
		*dst = 0xFF000000u | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
		*zbuf = dist;
		return ;
	}
	dstc = *dst;
	rgb[0] = (uint8_t)((rgb[0] * a + ((dstc >> 16) & 0xFF) * (255 - a)) / 255);
	rgb[1] = (uint8_t)((rgb[1] * a + ((dstc >> 8) & 0xFF) * (255 - a)) / 255);
	rgb[2] = (uint8_t)((rgb[2] * a + (dstc & 0xFF) * (255 - a)) / 255);
	*dst = 0xFF000000u | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (dist < *zbuf)
		*zbuf = dist;
}
