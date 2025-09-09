/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:47:02 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/29 16:27:06 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	map_validation3(t_config *cfg)
{
	int	i;

	i = 0;
	while (is_config_line(cfg->map[i]) || is_empty_line(cfg->map[i]))
		i++;
	return (validate_player(cfg, i));
}

bool	validate_player(t_config *cfg, int map_start)
{
	int	i;

	while (cfg->map[map_start])
	{
		i = 0;
		while (cfg->map[map_start][i])
		{
			if (cfg->map[map_start][i] == 'N' ||
				cfg->map[map_start][i] == 'S' ||
				cfg->map[map_start][i] == 'W' || cfg->map[map_start][i] == 'E')
			{
				cfg->player++;
				cfg->player_x = i;
				cfg->player_y = map_start;
				cfg->player_dir = cfg->map[map_start][i];
			}
			i++;
		}
		map_start++;
	}
	if (cfg->player != 1)
		return (print_err(cfg, "Error: there must be 1 player", -1));
	return (true);
}

void	set_path(char **dest, bool *seen, char *line, t_config *cfg)
{
	if (*seen)
	{
		exit(print_err(cfg, "Error: Duplicate asset", -1));
	}
	*seen = true;
	*dest = ft_strtrim(ft_strchr(line, ' '), " \t\n");
}

int	*color_atoia(const char *color_string)
{
	int		*rgb;
	char	**token;
	int		i;

	i = 0;
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	token = ft_split(color_string, ',');
	if (!token)
		return (free(rgb), NULL);
	while (token[i])
		i++;
	if (i != 3)
		return (free(rgb), free_split(token), NULL);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(token[i]))
			return (free(rgb), free_split(token), NULL);
		rgb[i] = ft_atoi(token[i]);
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (free(rgb), free_split(token), NULL);
	}
	return (free_split(token), rgb);
}

uint32_t	color_converter(int *rgb)
{
	uint32_t	color;

	color = 0xFF000000;
	color |= (rgb[2] << 16);
	color |= (rgb[1] << 8);
	color |= rgb[0];
	return (color);
}
