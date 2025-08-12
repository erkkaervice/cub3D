/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/12 17:29:06 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_floor_ceiling(t_game *game)
{
	uint32_t	*p;
	uint32_t	c;
	uint32_t	f;
	int			i;
	int			lim;

	p = (uint32_t *)game->img->pixels;
	c = game->cfg->ceiling_color;
	f = game->cfg->floor_color;
	lim = WIDTH * HEIGHT;
	i = 0;
	while (i < lim / 2)
		p[i++] = c;
	while (i < lim)
		p[i++] = f;
}

static void	draw_column_pixels(t_game *game, t_wall *wall, int x, int tex_id)
{
	t_texture	*tex;
	float		step;
	float		pos;
	int			y;
	int			tex_y;

	tex = game->textures[tex_id];
	step = (float)tex->height / (float)wall->line_height;
	pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		*((uint32_t *)game->img->pixels + y * WIDTH + x)
			= get_texture_color(game, tex_id, wall->tex_x, tex_y);
		pos += step;
		y++;
	}
}

static void	draw_column_loop(t_game *game, int x, t_wall *wall, int tex_id)
{
	t_texture	*tex;

	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return ;
	tex = game->textures[tex_id];
	if (!tex || !tex->image)
		return ;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	draw_column_pixels(game, wall, x, tex_id);
}

static void	render_column(t_game *game, int x)
{
	t_ray	ray;
	t_wall	wall;
	int		tex_id;
	int		hit;

	init_ray_basic(game, x, &ray);
	init_ray_steps(game, &ray);
	ray.perp_wall_dist = 1e30f;
	hit = perform_dda(game, &ray);
	if (hit == 0)
		return ;
	if (hit == 2 && handle_door_hit(game, &ray, &wall, &tex_id) == 0)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = 4;
	}
	else if (hit == 1)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = get_texture_index(ray.side, ray.ray_dir_x, ray.ray_dir_y);
	}
	wall.tex_x = get_tex_x(game, &ray, wall.wall_x, tex_id);
	draw_column_loop(game, x, &wall, tex_id);
}

void	render_frame(void *param)
{
	static double	last_time;
	t_game			*game;
	int				x;
	double			frame_time;
	double			current_time;

	game = (t_game *)param;
	current_time = mlx_get_time();
	frame_time = current_time - last_time;
	last_time = current_time;
	fill_floor_ceiling(game);
	update_doors(game);
	apply_mouse_look(game, frame_time);
	update_player_position(game);
	x = 0;
	while (x < WIDTH)
	{
		render_column(game, x);
		x++;
	}
	if (game->minimap_visible)
		render_minimap(game);
	if (game->fps_visible)
		render_fps(game);
}
