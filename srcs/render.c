/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/06 15:57:30 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_x(t_game *game, t_ray *ray, float wall_x)
{
	int		tex_x;
	int		tex_w;
	int		tex_id;

	tex_id = get_texture_index(ray->side,
			ray->ray_dir_x, ray->ray_dir_y);
	tex_w = game->textures[tex_id]->width;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * tex_w);
	if (tex_x >= tex_w)
		tex_x = tex_w - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex_w - tex_x - 1;
	return (tex_x);
}

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

void	draw_column_loop(t_game *game, int x, t_wall *wall, int tex_id)
{
	t_texture	*tex;
	uint32_t	*pix;
	int			y;
	float		step;
	float		pos;

	tex = game->textures[tex_id];
	step = (float)tex->height / wall->line_height;
	pos = (wall->draw_start - HEIGHT / 2
			+ wall->line_height / 2) * step;
	pix = (uint32_t *)game->img->pixels
		+ wall->draw_start * WIDTH + x;
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		*pix = get_texture_color(game,
				tex_id,
				wall->tex_x,
				(int)pos & (tex->height - 1));
		pos += step;
		pix += WIDTH;
		y++;
	}
}

void	draw_column(t_game *game, int x, t_wall *wall, t_ray *ray)
{
	int	tex_id;

	tex_id = get_texture_index(ray->side,
			ray->ray_dir_x, ray->ray_dir_y);
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
	if (game->minimap_visible)
		render_minimap(game);
	if (game->fps_visible)
		render_fps(game);
}
