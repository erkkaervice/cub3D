/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:43:52 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/01 16:05:48 by eala-lah         ###   ########.fr       */
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
			if (map[y][x++] == TILE_SPRITE)
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
	if (g->num_sprites > MAX_SPRITES)
		g->num_sprites = MAX_SPRITES;
	g->sprites = malloc(sizeof(t_sprite) * g->num_sprites);
	if (!g->sprites)
		exit(EXIT_FAILURE);
	i = 0;
	y = -1;
	while (g->cfg->map[++y])
	{
		x = -1;
		while (g->cfg->map[y][++x])
			if (g->cfg->map[y][x] == TILE_SPRITE && i < g->num_sprites)
				init_sprite(g, &g->sprites[i++], x, y);
	}
}

void	update_sprite_distances(t_game *g)
{
	int		i;
	float	dx;
	float	dy;

	i = 0;
	while (i < g->num_sprites)
	{
		dx = g->sprites[i].x - g->player_x;
		dy = g->sprites[i].y - g->player_y;
		g->sprites[i].dist = sqrtf(dx * dx + dy * dy);
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
		{
			if (g->sprites[i].dist < g->sprites[j].dist)
			{
				tmp = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = tmp;
			}
		}
	}
}

void	render_sprites(t_game *g, float *zb)
{
	int		i;
	float	dt;

	if (!g->num_sprites)
		return ;
	if (g->fps.fps > 0)
		dt = 1.0f / g->fps.fps;
	else
		dt = FRAME_DT;
	i = 0;
	while (i < g->num_sprites)
	{
		update_sprite(g, &g->sprites[i], dt);
		i++;
	}
	update_sprite_distances(g);
	sort_sprites(g);
	i = 0;
	while (i < g->num_sprites)
	{
		if (init_sprite_render(g, &g->sprites[i]))
			draw_sprite_stripe(g, &g->sprites[i], zb);
		i++;
	}
}
