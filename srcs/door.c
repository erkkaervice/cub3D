/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:25 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 18:38:57 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_ray_for_door(t_ray *ray, float open_ratio)
{
	if (ray->side == 0)
		ray->side_dist_x -= open_ratio * ray->step_x;
	else
		ray->side_dist_y -= open_ratio * ray->step_y;
}

int	find_door_index(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

int	get_tex_id_for_hit(t_game *game, t_ray *ray)
{
	char	cell;

	if (ray->map_y < 0 || ray->map_x < 0)
		return (-1);
	cell = game->cfg->map[ray->map_y][ray->map_x];
	if (cell == 'D')
		return (get_texture_index_door(game, ray->map_x, ray->map_y));
	else if (cell == '1')
		return (get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y));
	return (-1);
}

void	init_doors(t_game *game)
{
	int		y;
	int		x;
	int		count;
	char	**map;

	map = game->cfg->map;
	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	game->doors = malloc(sizeof(t_door) * count);
	if (!game->doors)
		return ; // handle error
	game->num_doors = count;
	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
			{
				game->doors[count].x = x;
				game->doors[count].y = y;
				game->doors[count].open_ratio = 0.0f;
				game->doors[count].is_opening = 0;
				count++;
			}
			x++;
		}
		y++;
	}
}

void	toggle_door(t_game *game)
{
	int		x;
	int		y;
	int		i;
	float	check_x;
	float	check_y;

	if (!game || !game->doors)
		return ;
	check_x = game->player_x + game->dir_x * 0.8f;
	check_y = game->player_y + game->dir_y * 0.8f;
	x = (int)check_x;
	y = (int)check_y;
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
		{
			if (game->doors[i].is_opening)
				game->doors[i].is_opening = 0; // stop opening (start closing)
			else
				game->doors[i].is_opening = 1; // start opening
			break ;
		}
		i++;
	}
}

/*
 * Call this each frame to update doors' open_ratio.
 */
void	update_doors(t_game *game)
{
	int		i;
	float	speed;

	if (!game || !game->doors)
		return ;
	speed = 0.02f; // adjust speed as needed
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].is_opening && game->doors[i].open_ratio < 1.0f)
		{
			game->doors[i].open_ratio += speed;
			if (game->doors[i].open_ratio > 1.0f)
				game->doors[i].open_ratio = 1.0f;
		}
		else if (!game->doors[i].is_opening && game->doors[i].open_ratio > 0.0f)
		{
			game->doors[i].open_ratio -= speed;
			if (game->doors[i].open_ratio < 0.0f)
				game->doors[i].open_ratio = 0.0f;
		}
		i++;
	}
}
