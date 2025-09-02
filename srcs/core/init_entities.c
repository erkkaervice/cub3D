/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:14:34 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 19:22:29 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_game *g, t_sprite *s, int x, int y)
{
	s->x = x + RAY_HALF_TILE_OFFSET;
	s->y = y + RAY_HALF_TILE_OFFSET;
	s->perp_dist = 0.0f;
	s->texture_id = TEX_SPRITE_0;
	s->start_x = -1;
	s->end_x = -1;
	s->start_y = -1;
	s->end_y = -1;
	s->dist = 0.0f;
	s->frame_index = 0;
	s->anim_timer = 0.0f;
	s->speed = SPRITE_DEFAULT_SPEED;
	s->frames[0] = g->textures[TEX_SPRITE_0];
	s->frames[1] = g->textures[TEX_SPRITE_1];
	s->frames[2] = g->textures[TEX_SPRITE_2];
	s->chasing = SPRITE_DEFAULT_CHASING;
}

int	init_sprite_render(t_game *g, t_sprite *s)
{
	if (!compute_sprite_transform(g, s))
		return (0);
	compute_sprite_bounds(g, s);
	if (s->perp_dist <= RAY_MIN_PERP_DIST)
		return (0);
	return (1);
}

void	init_ray_basic(t_game *game, int x, t_ray *ray)
{
	float	camera_x;

	camera_x = 2.0f * x / (float)game->win_width - 1.0f;
	ray->ray_dir_x = game->dir_x + game->plane_x * camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * camera_x;
	ray->map_x = (int)game->player_x;
	ray->map_y = (int)game->player_y;
	if (ray->ray_dir_x == 0.0f)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = 1.0f / fabsf(ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0f)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = 1.0f / fabsf(ray->ray_dir_y);
}

void	init_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0.0f)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - game->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0.0f)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - game->player_y)
			* ray->delta_dist_y;
	}
}

void	init_mouse(t_game *game)
{
	game->mouse.dx = 0.0;
	game->mouse.sensitivity = MOUSE_SENSITIVITY;
	game->mouse.prev_x = game->win_width / 2;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->mlx, game->win_width / 2, game->win_height / 2);
}
