/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:25:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 16:15:42 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*mock_config(void)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	cfg->north_texture = ft_strdup("textures/north.xpm");
	cfg->south_texture = ft_strdup("textures/south.xpm");
	cfg->west_texture = ft_strdup("textures/west.xpm");
	cfg->east_texture = ft_strdup("textures/east.xpm");
	cfg->floor_color = (220 << 16) | (100 << 8) | 0;
	cfg->ceiling_color = (225 << 16) | (30 << 8) | 0;
	cfg->map = ft_split("111111\n100001\n1000N1\n111111", '\n');
	cfg->player_x = 4;
	cfg->player_y = 2;
	cfg->player_dir = 'N';
	return (cfg);
}
