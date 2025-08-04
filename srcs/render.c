/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:53:42 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 17:23:29 by eala-lah         ###   ########.fr       */
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
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * (float)tex_width);
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	if ((ray->side == 0 && ray->ray_dir_x > 0.0f)
		|| (ray->side == 1 && ray->ray_dir_y < 0.0f))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_floor_ceiling(t_game *game)
{
	int	y;
	int	x;
	int	*pixel;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = (int *)(game->addr
					+ y * game->line_len + x * (game->bpp / 8));
			if (y < HEIGHT / 2)
				*pixel = game->cfg->ceiling_color;
			else
				*pixel = game->cfg->floor_color;
			x++;
		}
		y++;
	}
}

static void	draw_column_loop(t_game *game, int x, t_wall *wall, int tex_id)
{
	int		y;
	int		d;
	int		tex_y;
	int		*pixel;

	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		d = (y * 256) - (HEIGHT * 128) + (wall->line_height * 128);
		tex_y = ((d * game->textures[tex_id]->height)
				/ wall->line_height) / 256;
		pixel = (int *)(game->addr + y * game->line_len + x * (game->bpp / 8));
		*pixel = get_texture_color(game, tex_id, wall->tex_x, tex_y);
		y++;
	}
}

void	draw_column(t_game *game, int x, t_wall *wall, t_ray *ray)
{
	int		tex_id;

	tex_id = get_texture_index(ray->side, ray->ray_dir_x, ray->ray_dir_y);
	draw_column_loop(game, x, wall, tex_id);
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_floor_ceiling(game);
	update_player_position(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
