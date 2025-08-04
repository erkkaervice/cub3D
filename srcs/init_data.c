/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:22:57 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:57:20 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_textures_null(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i] = NULL;
		i++;
	}
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->cfg = NULL;
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->player_x = 0.0f;
	game->player_y = 0.0f;
	game->dir_x = 0.0f;
	game->dir_y = 0.0f;
	game->plane_x = 0.0f;
	game->plane_y = 0.0f;
	game->input.w = 0;
	game->input.a = 0;
	game->input.s = 0;
	game->input.d = 0;
	game->input.left = 0;
	game->input.right = 0;
	init_textures_null(game);
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

	game->player_x = (float)game->cfg->player_x + 0.5f;
	game->player_y = (float)game->cfg->player_y + 0.5f;
	i = 0;
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
