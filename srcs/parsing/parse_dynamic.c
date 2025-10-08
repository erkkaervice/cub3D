/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dynamic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:47:02 by dvlachos          #+#    #+#             */
/*   Updated: 2025/10/07 13:55:14 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_count_sprites(char **map)
{
	int	i;
	int	x;
	int	y;

	if (!map)
		return (0);
	i = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == TILE_SPRITE)
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

void	spr_init_pos(t_game *g, int *i, int *y)
{
	int	x;

	*i = 0;
	*y = 0;
	while (g->cfg->map[*y] && *i < g->num_sprites)
	{
		x = 0;
		while (g->cfg->map[*y][x] && *i < g->num_sprites)
		{
			if (g->cfg->map[*y][x] == TILE_SPRITE)
			{
				init_spr(g, &g->sprites[*i], x, *y);
				(*i)++;
			}
			x++;
		}
		(*y)++;
	}
}

void	spr_parse(t_game *g)
{
	int	i;
	int	y;

	if (!g || !g->cfg || !g->cfg->map)
		ft_error("Invalid game configuration in parse_sprites");
	g->num_sprites = map_count_sprites(g->cfg->map);
	if (!g->num_sprites)
	{
		g->sprites = NULL;
		return ;
	}
	if (g->num_sprites > MAP_MAX_SPRITES)
		g->num_sprites = MAP_MAX_SPRITES;
	g->sprites = ft_calloc(g->num_sprites, sizeof(t_sprite));
	if (!g->sprites)
		ft_error("Failed to allocate memory for sprites");
	spr_init_pos(g, &i, &y);
}

void	map_valid_struct(t_config *cfg, int start_line)
{
	int	*rgb;

	rgb = rgb_parse_array(cfg->floor_color);
	free(rgb);
	rgb = rgb_parse_array(cfg->ceiling_color);
	free(rgb);
	while (cfg_is_line(cfg->map[start_line])
		|| ft_isemptyline(cfg->map[start_line]))
		start_line++;
	map_valid_player(cfg, start_line);
}

bool	map_valid_player(t_config *cfg, int map_start)
{
	int		player_count;
	int		i;
	char	c;

	player_count = 0;
	while (cfg->map[map_start])
	{
		i = 0;
		while (cfg->map[map_start][i])
		{
			c = cfg->map[map_start][i];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				player_count++;
				cfg->player_x = i;
				cfg->player_y = map_start;
				cfg->player_dir = c;
			}
			i++;
		}
		map_start++;
	}
	if (player_count != 1)
		ft_error("Error: there must be 1 player");
	return (true);
}
