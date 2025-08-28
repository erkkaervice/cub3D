/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/28 17:23:54 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct_arrays(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->textures[i] = NULL;
		i++;
	}
	game->input = (t_input){0};
	game->fps.frames = 0;
	game->fps.fps = 0;
	game->fps.last_time = clock();
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->img = NULL;
	game->frame = NULL;
	game->cfg = NULL;
	game->player_x = 0.0f;
	game->player_y = 0.0f;
	game->dir_x = 0.0f;
	game->dir_y = 0.0f;
	game->plane_x = 0.0f;
	game->plane_y = 0.0f;
	game->doors = NULL;
	game->num_doors = 0;
	game->sprites = NULL;
	game->num_sprites = 0;
	game->z_buffer = NULL;
	init_struct_arrays(game);
	game->win_width = WIDTH;
	game->win_height = HEIGHT;
	game->scale_x = 1.0f;
	game->scale_y = 1.0f;
	game->needs_blit = 1;
}

void	init_dir_infos(t_game *game)
{
	game->dir_infos[0] = (t_dir_info){DIR_NORTH, DIR_NORTH_X, DIR_NORTH_Y,
		DIR_NORTH_PLANE_X, DIR_NORTH_PLANE_Y};
	game->dir_infos[1] = (t_dir_info){DIR_SOUTH, DIR_SOUTH_X, DIR_SOUTH_Y,
		DIR_SOUTH_PLANE_X, DIR_SOUTH_PLANE_Y};
	game->dir_infos[2] = (t_dir_info){DIR_EAST, DIR_EAST_X, DIR_EAST_Y,
		DIR_EAST_PLANE_X, DIR_EAST_PLANE_Y};
	game->dir_infos[3] = (t_dir_info){DIR_WEST, DIR_WEST_X, DIR_WEST_Y,
		DIR_WEST_PLANE_X, DIR_WEST_PLANE_Y};
}

void	init_player(t_game *game)
{
	int	i;

	i = 0;
	game->player_x = game->cfg->player_x + 0.5f;
	game->player_y = game->cfg->player_y + 0.5f;
	while (i < DIR_COUNT)
	{
		if (game->dir_infos[i].dir == game->cfg->player_dir)
		{
			game->dir_x = game->dir_infos[i].dir_x;
			game->dir_y = game->dir_infos[i].dir_y;
			game->plane_x = game->dir_infos[i].plane_x;
			game->plane_y = game->dir_infos[i].plane_y;
			break ;
		}
		i++;
	}
}

void	init_doors(t_game *game)
{
	int	y;
	int	x;
	int	idx;

	game->num_doors = count_doors(game);
	if (game->num_doors == 0)
		return ;
	game->doors = malloc(sizeof(t_door) * game->num_doors);
	if (!game->doors)
		return ;
	idx = 0;
	y = 0;
	while (game->cfg->map[y])
	{
		x = 0;
		while (game->cfg->map[y][x])
		{
			if (game->cfg->map[y][x] == TILE_DOOR)
			{
				game->doors[idx++] = (t_door){x, y, DOOR_INITIAL_OPEN_RATIO, 0};
			}
			x++;
		}
		y++;
	}
}
