/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 16:54:58 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_floor_ceiling(t_game *game)
{
	uint32_t	*p;
	int			i;
	int			lim;

	p = (uint32_t *)game->img->pixels;
	lim = WIDTH * HEIGHT;
	i = 0;
	while (i < lim / 2)
		p[i++] = CEILING_COLOR;
	while (i < lim)
		p[i++] = FLOOR_COLOR;
}

static void	draw_column_pixels(t_game *game, t_wall *wall, int x, int tex_id, float *z_buffer)
{
	t_texture	*tex;
	float		step;
	float		pos;
	int			y;
	int			tex_y;
	uint32_t	*dst;
	uint32_t	src;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	int			do_blend;

	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return ;
	tex = game->textures[tex_id];
	if (!tex || tex->height <= 0)
		return ;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;

	step = (float)tex->height / (float)wall->line_height;
	pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
	dst = (uint32_t *)game->img->pixels;
	y = wall->draw_start;
	do_blend = (tex_id == TEX_SPRITE || tex_id == TEX_DOOR);

	while (y <= wall->draw_end)
	{
		if ((do_blend) && (wall->perp_wall_dist >= z_buffer[x]))
		{
			y++;
			pos += step;
			continue;
		}
		tex_y = (int)pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;

		src = get_texture_color(game, tex_id, wall->tex_x, tex_y);
		b = (src >> 16) & 0xFF;
		g = (src >> 8) & 0xFF;
		r = src & 0xFF;
		a = (src >> 24) & 0xFF;

		if (!do_blend || a == 255)
			dst[y * WIDTH + x] = 0xFF000000u | (r << 16) | (g << 8) | b;
		else if (a != 0)
		{
			uint32_t dstc = dst[y * WIDTH + x];
			uint8_t dr = (dstc >> 16) & 0xFF;
			uint8_t dg = (dstc >> 8) & 0xFF;
			uint8_t db = dstc & 0xFF;

			r = (uint8_t)((r * a + dr * (255 - a)) / 255);
			g = (uint8_t)((g * a + dg * (255 - a)) / 255);
			b = (uint8_t)((b * a + db * (255 - a)) / 255);

			dst[y * WIDTH + x] = 0xFF000000u | (r << 16) | (g << 8) | b;
		}
		pos += step;
		y++;
	}
}

static void	draw_column_loop(t_game *game, int x, t_wall *wall, int tex_id, float *z_buffer)
{
	if (tex_id < 0 || tex_id >= TEXTURE_COUNT)
		return ;
	if (!game->textures[tex_id] || !game->textures[tex_id]->image)
		return ;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	draw_column_pixels(game, wall, x, tex_id, z_buffer);
}

static void	render_column(t_game *game, int x, float *z_buffer)
{
	t_ray	ray;
	t_wall	wall;
	int		tex_id;
	int		hit;

	init_ray_basic(game, x, &ray);
	init_ray_steps(game, &ray);
	ray.perp_wall_dist = RAY_MAX_DIST;
	hit = perform_dda(game, &ray, x);
	if (hit == 0)
	{
		z_buffer[x] = INFINITY;
		return ;
	}
	if (hit == 2 && handle_door_hit(game, &ray, &wall, &tex_id) == 0)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = TEX_DOOR;
	}
	else if (hit == 1)
	{
		calculate_wall(game, &ray, &wall);
		tex_id = get_texture_index(ray.side, ray.ray_dir_x, ray.ray_dir_y);
	}
	z_buffer[x] = ray.perp_wall_dist;
	wall.tex_x = get_tex_x(game, &ray, wall.wall_x, tex_id);
	draw_column_loop(game, x, &wall, tex_id, z_buffer);
}


void	render_frame(void *param)
{
	static double	last_time;
	t_game			*game;
	int				i;
	int				x;
	double			frame_time;
	double			current_time;
	float			z_buffer[WIDTH];

	game = (t_game *)param;
	current_time = mlx_get_time();
	frame_time = current_time - last_time;
	last_time = current_time;
	fill_floor_ceiling(game);
	update_doors(game);
	apply_mouse_look(game, frame_time);
	update_player_position(game);
	i = 0;
	while (i < WIDTH)
	{
		z_buffer[i] = INFINITY;
		i++;
	}
	x = 0;
	while (x < WIDTH)
	{
		render_column(game, x, z_buffer);
		x++;
	}
	render_sprites(game, z_buffer);
	if (game->minimap_visible)
		render_minimap(game);
	if (game->fps_visible)
		render_fps(game);
}
