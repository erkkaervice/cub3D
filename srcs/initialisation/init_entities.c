/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:22:02 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 15:38:48 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	doors_count(const t_game *g)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (g->cfg->map[y])
	{
		x = 0;
		while (g->cfg->map[y][x])
		{
			if (g->cfg->map[y][x] == TILE_DOOR)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	doors_init(t_game *g)
{
	int	y;
	int	x;
	int	i;

	g->num_doors = doors_count(g);
	if (g->num_doors == 0)
		return ;
	g->doors = ft_calloc(g->num_doors, sizeof(t_door));
	if (!g->doors)
		return ;
	i = 0;
	y = 0;
	while (g->cfg->map[y])
	{
		x = 0;
		while (g->cfg->map[y][x])
		{
			if (g->cfg->map[y][x] == TILE_DOOR)
				g->doors[i++] = (t_door)
				{x, y, DOOR_CLOSED, DOOR_OPEN_RATIO_START};
			x++;
		}
		y++;
	}
}

void	init_spr(t_game *g, t_sprite *s, int x, int y)
{
	s->x = x + RAY_HALF_TILE_OFFSET;
	s->y = y + RAY_HALF_TILE_OFFSET;
	s->perp_dist = 0.0f;
	s->start_x = -1;
	s->end_x = -1;
	s->start_y = -1;
	s->end_y = -1;
	s->dist = 0.0f;
	s->frame_index = 0;
	s->anim_timer = 0.0f;
	s->speed = SPRITE_DEFAULT_SPEED;
	s->frames[0] = g->tex[TEX_SPRITE_0];
	s->frames[1] = g->tex[TEX_SPRITE_1];
	s->frames[2] = g->tex[TEX_SPRITE_2];
	s->chasing = SPRITE_DEFAULT_CHASING;
	s->stopped = 0;
	s->active = 1;
}

int	init_spr_render(t_game *g, t_sprite *s)
{
	if (!spr_project(g, s))
		return (0);
	spr_bounds(g, s);
	if (s->perp_dist > RAY_MIN_PERP_DIST)
		return (1);
	return (0);
}

int	spr_reset(t_game *g)
{
	int	i;

	g->z_buffer = ft_calloc(g->win_width, sizeof(float));
	if (!g->z_buffer)
		return (0);
	i = 0;
	while (i < g->num_sprites)
	{
		g->sprites[i].frame_index = 0;
		g->sprites[i].anim_timer = 0.0f;
		g->sprites[i].stopped = 0;
		g->sprites[i].active = 1;
		i++;
	}
	return (1);
}
