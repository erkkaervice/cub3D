/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:32:32 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 18:23:03 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(mlx_t *mlx, t_texture *texture, char *path)
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
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	int		i;
	char	*paths[5];

	paths[0] = game->cfg->north_texture;
	paths[1] = game->cfg->south_texture;
	paths[2] = game->cfg->west_texture;
	paths[3] = game->cfg->east_texture;
	paths[4] = game->cfg->door_texture;
	i = 0;
	while (i < 5)
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
			return (1);
		else
			return (0);
	}
	if (ray_dir_y > 0)
		return (3);
	return (2);
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
			if (game->doors[i].open_ratio == 0.0f) // closed door uses door texture
			{
				if (game->textures[4] && game->textures[4]->image)
					return (4);
				return (-1);
			}
			else // open door, no texture or floor texture maybe
				return (-1);
		}
		i++;
	}
	return (-1);
}

int	get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y)
{
	t_texture		*tex;
	unsigned char	*pixel;

	if ((unsigned int)tex_id >= 5)
		return (0);
	tex = game->textures[tex_id];
	if (!tex || !tex->image)
		return (0);
	if ((unsigned int)tex_x >= (unsigned int)tex->width)
		tex_x = tex->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)tex->height)
		tex_y = tex->height - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	pixel = (unsigned char *)(tex->image->pixels
			+ (tex_y * tex->image->width + tex_x) * 4);
	return ((int)(pixel[0] | (pixel[1] << 8) | (pixel[2] << 16)
		| (pixel[3] << 24)));
}
