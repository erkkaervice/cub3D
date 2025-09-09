/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:32:32 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 17:33:01 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_tex_file(mlx_t *mlx, t_tex *t, char *path, t_config *cfg)
{
	t->img = mlx_load_png(path);
	if (!t->img)
	{
		free_config_textures(cfg);
		return (0);
	}
	t->width = t->img->width;
	t->height = t->img->height;
	t->image = mlx_texture_to_image(mlx, t->img);
	if (!t->image)
	{
		mlx_delete_texture(t->img);
		t->img = NULL;
		return (0);
	}
	return (1);
}

int	load_tex(t_game *g)
{
	int		i;
	char	*paths[TEX_COUNT];

	paths[TEX_NORTH] = g->cfg->north_tex;
	paths[TEX_SOUTH] = g->cfg->south_tex;
	paths[TEX_WEST] = g->cfg->west_tex;
	paths[TEX_EAST] = g->cfg->east_tex;
	paths[TEX_DOOR] = g->cfg->door_tex;
	paths[TEX_SPRITE_0] = g->cfg->sprite_tex_0;
	paths[TEX_SPRITE_1] = g->cfg->sprite_tex_1;
	paths[TEX_SPRITE_2] = g->cfg->sprite_tex_2;
	i = 0;
	while (i < TEX_COUNT)
	{
		g->tex[i] = ft_calloc(1, sizeof(t_tex));
		if (!g->tex[i])
			return (free_textures(g, i), 0);
		if (!load_tex_file(g->mlx, g->tex[i], paths[i], g->cfg))
			return (free_textures(g, i + 1), 0);
		i++;
	}
	return (1);
}

int	get_tex_index(int side, float ray_dir_x, float ray_dir_y)
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

int	get_tex_color_from_tex(t_tex *t, int tex_x, int tex_y)
{
	t_tex			*tex;
	int				offset;
	unsigned char	*px;

	tex = t;
	if (!tex || !tex->img || !tex->img->pixels)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if ((unsigned int)tex_x >= (unsigned int)tex->width)
		tex_x = tex->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)tex->height)
		tex_y = tex->height - 1;
	offset = (tex_y * tex->width + tex_x) * BYTES_PER_PIXEL;
	px = (unsigned char *)tex->img->pixels + offset;
	if (px[3] == 0)
		return (0);
	return ((int)(px[3] << 24 | px[0] << 16 | px[1] << 8 | px[2]));
}

int	get_tex_color(t_game *g, int tex_id, int tex_x, int tex_y)
{
	t_tex			*t;
	int				offset;
	unsigned char	*px;

	if ((unsigned int)tex_id >= TEX_COUNT)
		return (0);
	t = g->tex[tex_id];
	if (!t || !t->img || !t->img->pixels)
		return (0);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if ((unsigned int)tex_x >= (unsigned int)t->width)
		tex_x = t->width - 1;
	if ((unsigned int)tex_y >= (unsigned int)t->height)
		tex_y = t->height - 1;
	offset = (tex_y * t->width + tex_x) * BYTES_PER_PIXEL;
	px = (unsigned char *)t->img->pixels + offset;
	if (px[3] == 0)
		return (0);
	return ((int)(px[3] << 24 | px[0] << 16 | px[1] << 8 | px[2]));
}
