/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 14:04:03 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct_arrays(t_game *g)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		g->tex[i] = NULL;
		i++;
	}
	g->input = (t_input){0};
	g->fps.frames = 0;
	g->fps.fps = 0;
	g->fps.last_time = clock();
}

void	init_game_struct(t_game *g)
{
	g->mlx = NULL;
	g->img = NULL;
	g->frame = NULL;
	g->cfg = NULL;
	g->player_x = 0.0f;
	g->player_y = 0.0f;
	g->dir_x = 0.0f;
	g->dir_y = 0.0f;
	g->plane_x = 0.0f;
	g->plane_y = 0.0f;
	g->doors = NULL;
	g->num_doors = 0;
	g->sprites = NULL;
	g->num_sprites = 0;
	g->z_buffer = NULL;
	init_struct_arrays(g);
	g->scale_x = SPRITE_DEFAULT_SCALE;
	g->scale_y = SPRITE_DEFAULT_SCALE;
	g->needs_blit = 1;
}

void	init_dir_infos(t_game *g)
{
	g->dir_infos[0] = (t_dir_info){DIR_NORTH_CHAR, DIR_NORTH_X, DIR_NORTH_Y,
		DIR_NORTH_PLANE_X, DIR_NORTH_PLANE_Y};
	g->dir_infos[1] = (t_dir_info){DIR_SOUTH_CHAR, DIR_SOUTH_X, DIR_SOUTH_Y,
		DIR_SOUTH_PLANE_X, DIR_SOUTH_PLANE_Y};
	g->dir_infos[2] = (t_dir_info){DIR_EAST_CHAR, DIR_EAST_X, DIR_EAST_Y,
		DIR_EAST_PLANE_X, DIR_EAST_PLANE_Y};
	g->dir_infos[3] = (t_dir_info){DIR_WEST_CHAR, DIR_WEST_X, DIR_WEST_Y,
		DIR_WEST_PLANE_X, DIR_WEST_PLANE_Y};
}

void	init_player(t_game *g)
{
	int	i;

	if (!g || !g->cfg)
		return ;
	g->player_x = g->cfg->player_x + RAY_HALF_TILE_OFFSET;
	g->player_y = g->cfg->player_y + RAY_HALF_TILE_OFFSET;
	i = 0;
	while (i < DIR_COUNT)
	{
		if (g->dir_infos[i].dir == g->cfg->player_dir)
		{
			g->dir_x = g->dir_infos[i].dir_x;
			g->dir_y = g->dir_infos[i].dir_y;
			g->plane_x = g->dir_infos[i].plane_x;
			g->plane_y = g->dir_infos[i].plane_y;
			break ;
		}
		i++;
	}
}

void	init_doors(t_game *g)
{
	int	y;
	int	x;
	int	i;

	g->num_doors = count_doors(g);
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
				g->doors[i++] = (t_door){x, y, DOOR_OPEN_RATIO_START, 0};
			x++;
		}
		y++;
	}
}
