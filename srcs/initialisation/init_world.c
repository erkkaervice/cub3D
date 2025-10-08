/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:50 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 15:02:56 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*world_config(const char *f)
{
	t_config	*cfg;

	cfg = ft_calloc(1, sizeof(t_config));
	if (!cfg)
		return (NULL);
	if (!cfg_parse(cfg, f))
		return (free_cfg(&cfg), NULL);
	if (cfg->ceiling_color)
		cfg->ceiling_color_u32 = rgb_to_u32(cfg->ceiling_color);
	if (cfg->floor_color)
		cfg->floor_color_u32 = rgb_to_u32(cfg->floor_color);
	cfg->door_tex = ft_strdup(TEX_PATH_DOOR);
	cfg->sprite_tex = ft_calloc(4, sizeof(char *));
	if (!cfg->door_tex || !cfg->sprite_tex)
		return (free_cfg(&cfg), NULL);
	cfg->sprite_tex[0] = ft_strdup(TEX_PATH_SPRITE_0);
	cfg->sprite_tex[1] = ft_strdup(TEX_PATH_SPRITE_1);
	cfg->sprite_tex[2] = ft_strdup(TEX_PATH_SPRITE_2);
	if (!cfg->sprite_tex[0] || !cfg->sprite_tex[1] || !cfg->sprite_tex[2])
		return (free_cfg(&cfg), NULL);
	return (cfg);
}

int	map_load(t_config *cfg, const char *filename)
{
	int	lines;
	int	max_len;
	int	i;

	lines = map_count_lines(filename);
	cfg->map = ft_calloc(lines + 1, sizeof(char *));
	if (!cfg->map)
		ft_error("Malloc failed for map array");
	max_len = map_fill_lines(cfg, filename);
	i = 0;
	while (cfg->map[i] && !map_is_line(cfg->map[i]))
		i++;
	if (!cfg->map[i] || !map_valid_enc(cfg, i))
		ft_error("Error with map");
	return (max_len);
}

bool	map_normalize(t_config *cfg, int max_len)
{
	int		i;
	char	*new_line;

	i = 0;
	while (cfg->map[i])
	{
		if ((int)ft_strlen(cfg->map[i]) < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				ft_error("Malloc failed for map padding");
			ft_strlcpy(new_line, cfg->map[i], ft_strlen(cfg->map[i]) + 1);
			ft_memset(new_line + ft_strlen(cfg->map[i]), ' ',
				max_len - ft_strlen(cfg->map[i]));
			new_line[max_len] = '\0';
			free(cfg->map[i]);
			cfg->map[i] = new_line;
		}
		i++;
	}
	return (true);
}

int	tex_load_file(mlx_t *mlx, t_tex *t, char *path, t_config *cfg)
{
	if (!mlx || !t || !path || !cfg)
		return (0);
	t->tex = mlx_load_png(path);
	if (!t->tex)
	{
		free_cfg_tex(cfg);
		return (0);
	}
	t->width = t->tex->width;
	t->height = t->tex->height;
	t->img = mlx_texture_to_image(mlx, t->tex);
	if (!t->img)
	{
		mlx_delete_texture(t->tex);
		t->tex = NULL;
		return (0);
	}
	t->pixels32 = (uint32_t *)t->img->pixels;
	t->row_stride = t->width;
	return (1);
}

int	tex_load_all(t_game *g)
{
	int		i;
	char	*paths[TEX_COUNT];

	paths[TEX_NORTH] = g->cfg->north_tex;
	paths[TEX_SOUTH] = g->cfg->south_tex;
	paths[TEX_WEST] = g->cfg->west_tex;
	paths[TEX_EAST] = g->cfg->east_tex;
	paths[TEX_DOOR] = g->cfg->door_tex;
	paths[TEX_SPRITE_0] = g->cfg->sprite_tex[0];
	paths[TEX_SPRITE_1] = g->cfg->sprite_tex[1];
	paths[TEX_SPRITE_2] = g->cfg->sprite_tex[2];
	i = 0;
	while (i < TEX_COUNT)
	{
		g->tex[i] = ft_calloc(1, sizeof(t_tex));
		if (!g->tex[i])
			return (free_tex(g), (0));
		if (!tex_load_file(g->mlx, g->tex[i], paths[i], g->cfg))
			return (free_tex(g), (0));
		i++;
	}
	return (1);
}
