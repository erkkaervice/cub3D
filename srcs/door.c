/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:02:25 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 20:07:34 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_id_for_hit(t_game *game, t_ray *ray)
{
	char	cell;

	if (ray->map_y < 0 || ray->map_x < 0)
		return (-1);
	cell = game->cfg->map[ray->map_y][ray->map_x];
	if (cell == 'D')
		return (get_texture_index_door(game, ray->map_x, ray->map_y));
	if (cell == '1')
		return (get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y));
	return (-1);
}

void	toggle_door(t_game *game)
{
	int		x;
	int		y;
	int		i;
	float	check_x;
	float	check_y;

	check_x = game->player_x + game->dir_x * 0.8f;
	check_y = game->player_y + game->dir_y * 0.8f;
	x = (int)check_x;
	y = (int)check_y;
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
		{
			game->doors[i].is_opening = !game->doors[i].is_opening;
			break ;
		}
		i++;
	}
}

void	update_doors(t_game *game)
{
	int		i;
	float	speed;

	if (!game || !game->doors)
		return ;
	speed = 0.02f;
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].is_opening)
		{
			game->doors[i].open_ratio += speed;
			if (game->doors[i].open_ratio > 1.0f)
				game->doors[i].open_ratio = 1.0f;
		}
		else
		{
			game->doors[i].open_ratio -= speed;
			if (game->doors[i].open_ratio < 0.0f)
				game->doors[i].open_ratio = 0.0f;
		}
		i++;
	}
}

int	handle_door(t_game *game, t_ray *ray)
{
	int		door_idx;
	float	open_ratio;

	door_idx = find_door_index(game, ray->map_x, ray->map_y);
	if (door_idx < 0)
		return (2);
	open_ratio = game->doors[door_idx].open_ratio;
	if (open_ratio > 0.0f && open_ratio < 1.0f)
		return (-1);
	if (open_ratio >= 1.0f)
		return (-1);
	return (2);
}

int	handle_door_hit(t_game *game, t_ray *ray, t_wall *wall, int *tex_id)
{
	int		door_index;
	float	offset;

	door_index = find_door_index(game, ray->map_x, ray->map_y);
	if (door_index < 0)
		return (0);
	offset = game->doors[door_index].open_ratio;
	if (offset > 1.0f)
		offset = 1.0f;
	if (offset < 0.0f)
		offset = 0.0f;
	if (ray->side == 0)
		ray->side_dist_x -= offset * ray->step_x;
	else
		ray->side_dist_y -= offset * ray->step_y;
	calculate_wall(game, ray, wall);
	*tex_id = get_texture_index_door(game, ray->map_x, ray->map_y);
	return (1);
}
