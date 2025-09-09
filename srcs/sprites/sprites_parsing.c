/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:43:52 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 23:30:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_sprites(char **m)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == TILE_SPRITE)
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

void	parse_sprites(t_game *g)
{
	int	x;
	int	y;
	int	i;

	if (!g || !g->cfg || !g->cfg->map)
		ft_error("Invalid game configuration in parse_sprites");
	g->num_sprites = count_sprites(g->cfg->map);
	if (!g->num_sprites)
		return ;
	if (g->num_sprites > MAP_MAX_SPRITES)
		g->num_sprites = MAP_MAX_SPRITES;
	g->sprites = ft_calloc(g->num_sprites, sizeof(t_sprite));
	if (!g->sprites)
		ft_error("Failed to allocate memory for sprites");
	i = 0;
	y = 0;
	while (g->cfg->map[y] && i < g->num_sprites)
	{
		x = 0;
		while (g->cfg->map[y][x] && i < g->num_sprites)
			if (g->cfg->map[y][x++] == TILE_SPRITE)
				init_sprite(g, &g->sprites[i++], x - 1, y);
		y++;
	}
}

void	update_sprite_distances(t_game *g)
{
	int		i;
	float	dx;
	float	dy;

	if (!g || !g->sprites)
		return ;
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

	if (!g || !g->sprites)
		return ;
	i = 0;
	while (i < g->num_sprites - 1)
	{
		j = i + 1;
		while (j < g->num_sprites)
		{
			if (g->sprites[i].dist < g->sprites[j].dist)
			{
				tmp = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites(t_game *g, float *zb)
{
	int		i;
	float	dt;

	if (!g || !g->sprites || !zb || g->num_sprites <= 0)
		return ;
	if (g->fps.fps > 0)
		dt = 1.0f / g->fps.fps;
	else
		dt = SPRITE_FRAME_DT;
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
