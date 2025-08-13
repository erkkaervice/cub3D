/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:32:32 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 16:45:17 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(mlx_t *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_load_png(path);
	if (!texture->img)
		return (0);
	texture->width = texture->img->width;
	texture->height = texture->img->height;
	texture->image = mlx_texture_to_image(mlx, texture->img);
	if (!texture->image)
	{
		mlx_delete_texture(texture->img);
		texture->img = NULL;
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	int		i;
	char	*paths[TEXTURE_COUNT];

	paths[TEX_NORTH] = game->cfg->north_texture;
	paths[TEX_SOUTH] = game->cfg->south_texture;
	paths[TEX_WEST] = game->cfg->west_texture;
	paths[TEX_EAST] = game->cfg->east_texture;
	paths[TEX_DOOR] = game->cfg->door_texture;
	paths[TEX_SPRITE] = game->cfg->sprite_texture;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->textures[i] = malloc(sizeof(t_texture));
		if (!game->textures[i])
		{
			free_textures(game, i);
			return (0);
		}
		if (!load_texture(game->mlx, game->textures[i], paths[i]))
		{
			free_textures(game, i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_texture_index(int side, float ray_dir_x, float ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (TEX_SOUTH);
		return (TEX_NORTH);
	}
	if (ray_dir_y > 0)
		return (TEX_EAST);
	return (TEX_WEST);
}

int	get_texture_index_door(t_game *game, int map_x, int map_y)
{
	int	i;

	if (!game || !game->doors)
		return (-1);
	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == map_x && game->doors[i].y == map_y)
		{
			if (game->doors[i].open_ratio == 0.0f)
			{
				if (game->textures[TEX_DOOR] && game->textures[TEX_DOOR]->image)
					return (TEX_DOOR);
				return (-1);
			}
			return (-1);
		}
		i++;
	}
	return (-1);
}

int	get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y)
{
	t_texture		*tex;
	unsigned char	*px;

	if ((unsigned int)tex_id >= TEXTURE_COUNT)
		return (0);
	tex = game->textures[tex_id];
	if (!tex || !tex->img || !tex->img->pixels)
		return (0);

	if (tex_x < 0) tex_x = 0;
	if (tex_y < 0) tex_y = 0;
	if ((unsigned int)tex_x >= (unsigned int)tex->width)
		tex_x = tex->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)tex->height)
		tex_y = tex->height - 1;

	px = (unsigned char *)tex->img->pixels
		+ (tex_y * tex->width + tex_x) * BYTES_PER_PIXEL;

	if (px[3] == 0)
		return (0);
	return ((int)(px[3] << 24 | px[0] << 16 | px[1] << 8 | px[2]));
}
