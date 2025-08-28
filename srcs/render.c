/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/28 18:38:47 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_floor_ceiling(t_game *game)
{
	uint32_t	*p;
	int			i;
	uint32_t	floor;
	uint32_t	ceiling;
	int			*rgb;

	p = (uint32_t *)game->frame->pixels;
	rgb = color_atoia(game->cfg->floor_color);
	floor = color_converter(rgb);
	free(rgb);
	rgb = color_atoia(game->cfg->ceiling_color);
	ceiling = color_converter(rgb);
	free(rgb);
	i = 0;
	while (i < WIDTH * HEIGHT / 2)
		p[i++] = ceiling;
	while (i < WIDTH * HEIGHT)
		p[i++] = floor;
}

static void	draw_column(t_game *game, t_wall *wall, int x, int tex_id)
{
	t_texture	*tex;
	float		step;
	float		pos;
	int			y;

	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return ;
	tex = game->textures[tex_id];
	if (!tex || !tex->image || tex->height <= 0)
		return ;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	step = (float)tex->height / (float)wall->line_height;
	pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		blend_write_pixel(((uint32_t *)game->frame->pixels) + (y * WIDTH + x),
			get_texture_color(game, tex_id, wall->tex_x, (int)pos),
			&game->z_buffer[x], wall->perp_wall_dist);
		pos += step;
		y++;
	}
}

static void	render_column(t_game *game, int x)
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

void	blit_scaled(t_game *game)
{
	int			x;
	int			y;
	uint32_t	*dst;
	float		scale[4];

	if (!game->frame || !game->img)
		return ;
	scale[0] = (float)WIDTH / (float)game->win_width;
	scale[1] = (float)HEIGHT / (float)game->win_height;
	dst = (uint32_t *)game->img->pixels;
	y = 0;
	scale[3] = 0;
	while (y < game->win_height)
	{
		x = 0;
		scale[2] = 0;
		while (x < game->win_width)
		{
			dst[y * game->win_width + x]
				= ((uint32_t *)game->frame->pixels)
			[(int)scale[3] * WIDTH + (int)scale[2]];
			scale[2] += scale[0];
			x++;
		}
		scale[3] += scale[1];
		y++;
	}
}

static void	render_game_columns(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		render_column(game, x);
		x++;
	}
}

void	render_frame(void *param)
{
	static double	last_time;
	t_game			*game;
	double			current_time;
	double			frame_time;

	game = (t_game *)param;
	current_time = mlx_get_time();
	frame_time = current_time - last_time;
	last_time = current_time;
	fill_floor_ceiling(game);
	update_doors(game);
	apply_mouse_look(game, frame_time);
	update_player_position(game);
	render_game_columns(game);
	render_sprites(game, game->z_buffer);
	if (game->minimap_visible)
		render_minimap(game);
	if (game->fps_visible)
		render_fps(game);
	blit_scaled(game);
}
