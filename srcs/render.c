/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/05 18:29:40 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_x(t_game *game, t_ray *ray, float wall_x)
{
	int		tex_x;
	int		tex_width;
	int		tex_id;

	tex_id = get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y);
	tex_width = game->textures[tex_id]->width;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * tex_width);
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

static void	fill_floor_ceiling(t_game *game)
{
	uint32_t	*pixels;
	uint32_t	ceiling;
	uint32_t	floor;
	int			i;
	int			half;

	pixels = (uint32_t *)game->img->pixels;
	ceiling = game->cfg->ceiling_color;
	floor = game->cfg->floor_color;
	half = (WIDTH * HEIGHT) / 2;
	i = 0;
	while (i < half)
	{
		pixels[i] = ceiling;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		pixels[i] = floor;
		i++;
	}
}

void	draw_column_loop(t_game *game, int x, t_wall *wall, int tex_id)
{
	t_texture	*tex;
	uint32_t	*pixel;
	int			y;
	float		step;
	float		tex_pos;

	tex = game->textures[tex_id];
	step = (float)tex->height / wall->line_height;
	tex_pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
	pixel = (uint32_t *)game->img->pixels + wall->draw_start * WIDTH + x;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		*pixel = get_texture_color(game, tex_id, wall->tex_x,
				(int)tex_pos & (tex->height - 1));
		tex_pos += step;
		pixel += WIDTH;
		y++;
	}
}

void	draw_column(t_game *game, int x, t_wall *wall, t_ray *ray)
{
	int	tex_id;

	tex_id = get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y);
	draw_column_loop(game, x, wall, tex_id);
}

void	render_frame(void *param)
{
	t_game	*game;
	int		x;
	t_ray	ray;
	t_wall	wall;

	game = (t_game *)param;
	fill_floor_ceiling(game);
	update_player_position(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray_basic(game, x, &ray);
		init_ray_steps(game, &ray);
		if (!perform_dda(game, &ray))
		{
			x++;
			continue ;
		}
		calculate_wall(game, &ray, &wall);
		draw_column(game, x, &wall, &ray);
		x++;
	}
}
