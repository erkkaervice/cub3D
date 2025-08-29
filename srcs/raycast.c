/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:55:14 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/29 17:50:25 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_ray(t_ray *ray, int axis)
{
	if (axis == AXIS_X)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = AXIS_X;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = AXIS_Y;
	}
}

int	handle_tile(t_game *game, t_ray *ray, int map_w, int map_h)
{
	char	tile;
	int		ret;

	if (ray->map_x < 0 || ray->map_x >= map_w
		|| ray->map_y < 0 || ray->map_y >= map_h)
		return (0);
	tile = game->cfg->map[ray->map_y][ray->map_x];
	if (tile == TILE_WALL)
		return (1);
	if (tile == TILE_DOOR)
	{
		ret = handle_door(game, ray);
		if (ret == -1)
			return (-1);
		return (ret);
	}
	return (-1);
}

int	get_tex_x(t_game *game, t_ray *ray, float wall_x, int tex_id)
{
	int			tex_x;
	t_texture	*tex;

	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return (0);
	tex = game->textures[tex_id];
	if (!tex || !tex->image)
		return (0);
	tex_x = (int)(wall_x * (float)tex->width);
	if ((ray->side == AXIS_X && ray->ray_dir_x > 0)
		|| (ray->side == AXIS_Y && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

int	perform_dda(t_game *game, t_ray *ray, int x)
{
	int		map_w;
	int		map_h;
	int		step_count;
	int		ret;

	map_w = map_width(game->cfg->map[0]);
	map_h = map_height(game->cfg->map);
	step_count = 0;
	while (step_count < MAX_DDA_STEPS)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_ray(ray, AXIS_X);
		else
			step_ray(ray, AXIS_Y);
		ret = handle_tile(game, ray, map_w, map_h);
		if (ret != -1)
		{
			game->z_buffer[x] = ray->perp_wall_dist;
			return (ret);
		}
		step_count++;
	}
	game->z_buffer[x] = ray->perp_wall_dist;
	return (0);
}

void	raycast_column(t_game *game, int x)
{
	t_ray	ray;
	t_wall	wall;
	int		tex_id;
	int		hit;

	game->z_buffer[x] = INFINITY;
	init_ray_basic(game, x, &ray);
	init_ray_steps(game, &ray);
	ray.perp_wall_dist = RAY_MAX_DIST;
	hit = perform_dda(game, &ray, x);
	if (hit == 0)
		return ;
	if (hit == 2 && door_hit(game, &ray, &wall, &tex_id) == 0)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = TEX_DOOR;
	}
	else if (hit == 1)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = get_texture_index(ray.side, ray.ray_dir_x, ray.ray_dir_y);
	}
	wall.tex_x = get_tex_x(game, &ray, wall.wall_x, tex_id);
	draw_column(game, &wall, x, tex_id);
}
