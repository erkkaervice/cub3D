/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 19:57:08 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_struct(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = NULL;
	game->img = NULL;
	game->cfg = NULL;
	game->player_x = 0.0f;
	game->player_y = 0.0f;
	game->dir_x = 0.0f;
	game->dir_y = 0.0f;
	game->plane_x = 0.0f;
	game->plane_y = 0.0f;
	game->input = (t_input){.w = 0, .a = 0, .s = 0, .d = 0,
		.left = 0, .right = 0, .shift = 0};
	while (i < 5)
	{
		game->textures[i] = NULL;
		i++;
	}
}

void	init_dir_infos(t_game *game)
{
	game->dir_infos[0] = (t_dir_info){'N', 0, -1, 0.66f, 0};
	game->dir_infos[1] = (t_dir_info){'S', 0, 1, -0.66f, 0};
	game->dir_infos[2] = (t_dir_info){'E', 1, 0, 0, 0.66f};
	game->dir_infos[3] = (t_dir_info){'W', -1, 0, 0, -0.66f};
}

void	init_player(t_game *game)
{
	int	i;

	i = 0;
	game->player_x = game->cfg->player_x + 0.5f;
	game->player_y = game->cfg->player_y + 0.5f;
	while (i < 4)
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

	if (!count_and_fill_doors(game))
		return ;
	idx = 0;
	y = 0;
	while (game->cfg->map[y])
	{
		x = 0;
		while (game->cfg->map[y][x])
		{
			if (game->cfg->map[y][x] == 'D')
			{
				game->doors[idx].x = x;
				game->doors[idx].y = y;
				game->doors[idx].open_ratio = 0.0f;
				game->doors[idx].is_opening = 0;
				idx++;
			}
			x++;
		}
		y++;
	}
}
