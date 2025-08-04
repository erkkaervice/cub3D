/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:32:32 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:48:43 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(void *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx,
			path, &texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->line_len, &texture->endian);
	if (!texture->addr)
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->cfg->north_texture;
	paths[1] = game->cfg->south_texture;
	paths[2] = game->cfg->west_texture;
	paths[3] = game->cfg->east_texture;
	i = 0;
	while (i < 4)
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
		return (0);
	}
	if (ray_dir_y > 0)
		return (3);
	return (2);
}

int	get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y)
{
	t_texture		*tex;
	unsigned int	color;

	if (tex_id < 0 || tex_id >= 4)
		return (0);
	tex = game->textures[tex_id];
	if (!tex || !tex->addr || tex->bpp <= 0)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	color = *(unsigned int *)(tex->addr + tex_y * tex->line_len
			+ tex_x * (tex->bpp / 8));
	return (color);
}
