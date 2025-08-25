/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:02:06 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/20 15:20:43 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S' && *line != 'E'
			&& *line != 'W' && *line != '\n' && *line != 'D'
			&& *line != 'X')
			return (false);
		line++;
	}
	return (true);
}

bool	is_config_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp("NO ", line, 3) == 0
		|| ft_strncmp("SO ", line, 3) == 0
		|| ft_strncmp("WE ", line, 3) == 0
		|| ft_strncmp("EA ", line, 3) == 0
		|| ft_strncmp("F ", line, 2) == 0
		|| ft_strncmp("C ", line, 2) == 0)
		return (true);
	else
		return (false);
}

bool	is_empty_line(char *line)
{
	if (*line == '\n')
		return (true);
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

int	print_err(t_config *cfg, char *error, int fd)
{
	(void)cfg;
	if (*error)
		ft_putendl_fd(error, 2);
	if (fd >= 0)
		close(fd);
	return (0);
}

void	free_partial_config(t_config *cfg)
{
	int	i;

	i = 0;
	if (!cfg)
		return ;
	if (cfg->map && cfg->map[i])
	{
		while (cfg->map[i])
			free(cfg->map[i++]);
	}
	if (cfg->map)
	{
		free(cfg->map);
	}
	free_cfg_textures(cfg);
	free(cfg);
}

void	free_cfg_textures(t_config *cfg)
{
	if (cfg->ceiling_color)
		free(cfg->ceiling_color);
	if (cfg->north_texture)
		free(cfg->north_texture);
	if (cfg->west_texture)
		free(cfg->west_texture);
	if (cfg->east_texture)
		free(cfg->east_texture);
	if (cfg->south_texture)
		free(cfg->south_texture);
	if (cfg->floor_color)
		free(cfg->floor_color);
}
