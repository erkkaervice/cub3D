/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:19:02 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 14:58:13 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tex_pixel(const t_tex *t, int tex_x, int tex_y)
{
	int				offset;
	unsigned char	*px;

	if (!t || !t->tex || !t->tex->pixels)
		return (0);
	if ((unsigned int)tex_x >= (unsigned int)t->width)
		tex_x = t->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)t->height)
		tex_y = t->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	offset = (tex_y * t->width + tex_x) * BYTES_PER_PIXEL;
	px = (unsigned char *)t->tex->pixels + offset;
	if (px[3] == 0)
		return (0);
	return ((px[3] << 24) | (px[0] << 16) | (px[1] << 8) | px[2]);
}

uint32_t	tex_color(const t_game *g, int tex_id, int tex_x, int tex_y)
{
	const t_tex	*t;
	uint32_t	color;

	if ((unsigned int)tex_id >= TEX_COUNT)
		return (0);
	t = g->tex[tex_id];
	if (!t || !t->pixels32)
		return (0);
	if ((unsigned int)tex_x >= (unsigned int)t->width)
		tex_x = t->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)t->height)
		tex_y = t->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	color = t->pixels32[tex_y * t->row_stride + tex_x];
	if ((color >> 24) == 0)
		return (0);
	return (0xFF000000u
		| ((color & 0xFF) << 16)
		| (((color >> 8) & 0xFF) << 8)
		| ((color >> 16) & 0xFF));
}
