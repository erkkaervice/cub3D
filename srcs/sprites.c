/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:43:52 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 17:05:38 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_sprites(char **map)
{
	int	c;
	int	y;
	int	x;

	c = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			if (map[y][x++] == 'S')
				c++;
		y++;
	}
	return (c);
}

void	parse_sprites(t_game *g)
{
	int	y;
	int	x;
	int	i;

	g->num_sprites = count_sprites(g->cfg->map);
	if (!g->num_sprites)
		return ;
	g->sprites = malloc(sizeof(t_sprite) * g->num_sprites);
	if (!g->sprites)
		exit(EXIT_FAILURE);
	i = 0;
	y = -1;
	while (g->cfg->map[++y])
	{
		x = -1;
		while (g->cfg->map[y][++x])
			if (g->cfg->map[y][x] == 'S')
			{
				g->sprites[i].x = x + 0.5f;
				g->sprites[i].y = y + 0.5f;
				g->sprites[i].perp_dist = 0;
				g->sprites[i++].texture_id = TEX_SPRITE;
			}
	}
}

void	update_sprite_distances(t_game *g)
{
	int		i;
	float	sx;
	float	sy;
	float	inv_det;

	inv_det = 1.0f / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	i = 0;
	while (i < g->num_sprites)
	{
		sx = g->sprites[i].x - g->player_x;
		sy = g->sprites[i].y - g->player_y;
		g->sprites[i].tx = inv_det * (g->dir_y * sx - g->dir_x * sy);
		g->sprites[i].ty = inv_det * (-g->plane_y * sx + g->plane_x * sy);
		g->sprites[i].perp_dist = g->sprites[i].ty;
		i++;
	}
}

static void	sort_sprites(t_game *g)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < g->num_sprites - 1)
	{
		j = i;
		while (++j < g->num_sprites)
			if (g->sprites[i].perp_dist < g->sprites[j].perp_dist)
			{
				tmp = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = tmp;
			}
	}
}

void	render_sprites(t_game *g, float *zb)
{
	int	i;

	if (!g->textures[TEX_SPRITE] || !g->textures[TEX_SPRITE]->image)
		return ;
	i = -1;
	while (++i < g->num_sprites)
		init_sprite_render(g, &g->sprites[i]);
	sort_sprites(g);
	i = -1;
	while (++i < g->num_sprites)
		draw_sprite_stripe(g, &g->sprites[i], zb);
}
