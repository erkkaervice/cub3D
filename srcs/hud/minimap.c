/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:16:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:29:43 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile_pixel(t_game *g, int x, int y, char tile)
{
	int	i;
	int	j;
	int	c;

	if (tile == TILE_WALL)
		c = MM_WALL_COLOR;
	else if (tile == TILE_DOOR)
		c = MM_DOOR_COLOR;
	else
		c = MM_FLOOR_COLOR;
	i = 0;
	while (i < MM_SCALE)
	{
		j = 0;
		while (j < MM_SCALE)
		{
			if (x * MM_SCALE + i >= 0 && x * MM_SCALE + i < (int)g->frame->width
				&& y * MM_SCALE + j >= 0 && y
				* MM_SCALE + j < (int)g->frame->height)
				((uint32_t *)g->frame->pixels)
				[(y * MM_SCALE + j) * g->frame->width + (x * MM_SCALE + i)] = c;
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
		if (*line == TILE_WALL || *line == TILE_FLOOR || *line == TILE_DOOR)
			break ;
		(*start)++;
	}
	*end = *start;
	while (g->cfg->map[*end])
	{
		line = g->cfg->map[*end];
		while (*line == ' ' || *line == '\t')
			line++;
		if (!(*line == TILE_WALL || *line == TILE_FLOOR || *line == TILE_DOOR))
			break ;
		(*end)++;
	}
}

static void	draw_entity(t_game *g, float x, float y, int color)
{
	int	size;
	int	i;
	int	j;
	int	px;
	int	py;

	size = MM_SCALE / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			px = (int)(x * MM_SCALE) + i;
			py = (int)(y * MM_SCALE) + j;
			if (px >= 0 && px < (int)g->frame->width && py >= 0
				&& py < (int)g->frame->height)
				((uint32_t *)g->frame->pixels)
				[py * g->frame->width + px] = color;
			j++;
		}
		i++;
	}
}

static void	draw_map(t_game *g, int start, int end)
{
	int	y;
	int	x;

	y = 0;
	while (start + y < end)
	{
		x = 0;
		while (g->cfg->map[start + y][x] && g->cfg->map[start + y][x] != '\n')
		{
			if (ft_strchr("012345678NSEWDPX", g->cfg->map[start + y][x]))
				draw_tile_pixel(g, x, y, g->cfg->map[start + y][x]);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_game *g)
{
	int		start;
	int		end;
	int		i;
	float	py;

	if (!g || !g->cfg || !g->cfg->map)
		return ;
	find_map_bounds(g, &start, &end);
	draw_map(g, start, end);
	py = g->player_y - start;
	draw_entity(g, g->player_x, py, MM_PLAYER_COLOR);
	i = 0;
	while (i < g->num_sprites)
	{
		py = g->sprites[i].y - start;
		draw_entity(g, g->sprites[i].x, py, MM_SPRITE_COLOR);
		i++;
	}
}
