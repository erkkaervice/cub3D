/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:16:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 18:10:22 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pixel(t_game *g, int x, int y, int color)
{
	uint32_t	*px;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	px = (uint32_t *)g->img->pixels + y * WIDTH + x;
	*px = color;
}

static void	draw_tile(t_game *g, int x, int y, char tile)
{
	int	i;
	int	j;
	int	c;

	if (tile == TILE_WALL)
		c = MINIMAP_WALL_COLOR;
	else if (tile == TILE_DOOR)
		c = MINIMAP_DOOR_COLOR;
	else if (tile == TILE_SPRITE)
		c = MINIMAP_SPRITE_COLOR;
	else
		c = MINIMAP_FLOOR_COLOR;
	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			draw_pixel(g, x * MINIMAP_SCALE + i,
				y * MINIMAP_SCALE + j, c);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *g, int map_start_y)
{
	int	i;
	int	j;
	int	size;
	int	px;
	int	py;

	size = MINIMAP_SCALE / 2;
	px = (int)(g->player_x * MINIMAP_SCALE);
	py = (int)((g->player_y - map_start_y) * MINIMAP_SCALE);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(g, px + i, py + j, MINIMAP_PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

static void	find_map_bounds(t_game *g, int *start, int *end)
{
	char	*line;

	*start = 0;
	while (g->cfg->map[*start])
	{
		line = g->cfg->map[*start];
		while (*line == ' ' || *line == '\t')
			line++;
		if (*line == TILE_WALL || *line == TILE_FLOOR
			|| *line == TILE_DOOR || *line == TILE_SPRITE)
			break ;
		(*start)++;
	}
	*end = *start;
	while (g->cfg->map[*end])
	{
		line = g->cfg->map[*end];
		while (*line == ' ' || *line == '\t')
			line++;
		if (!(*line == TILE_WALL || *line == TILE_FLOOR
				|| *line == TILE_DOOR || *line == TILE_SPRITE))
			break ;
		(*end)++;
	}
}

void	render_minimap(t_game *g)
{
	int		y;
	int		x;
	int		start;
	int		end;
	char	tile;

	if (!g || !g->cfg || !g->cfg->map)
		return ;
	find_map_bounds(g, &start, &end);
	y = 0;
	while (start + y < end)
	{
		x = 0;
		while (g->cfg->map[start + y][x] && g->cfg->map[start + y][x] != '\n')
		{
			tile = g->cfg->map[start + y][x];
			if (tile == TILE_WALL || tile == TILE_FLOOR
				|| tile == TILE_SPRITE || tile == TILE_SPAWN
				|| tile == TILE_DOOR)
				draw_tile(g, x, y, tile);
			x++;
		}
		y++;
	}
	draw_player(g, start);
}
