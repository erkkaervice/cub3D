/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:02:06 by dvlachos          #+#    #+#             */
/*   Updated: 2025/09/04 17:55:59 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_line(char *line)
{
	bool	has_map_char;

	has_map_char = false;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (false);
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || *line == 'D' || *line == 'X')
			has_map_char = true;
		else if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (has_map_char);
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
	if (!error)
	{
		if (fd >= 0)
			close (fd);
		return (0);
	}
	if (*error)
		ft_putendl_fd(error, 2);
	if (fd >= 0)
		close(fd);
	return (0);
}

void	free_cfg_tex(t_config *cfg)
{
	if (cfg->ceiling_color)
		free(cfg->ceiling_color);
	if (cfg->north_tex)
		free(cfg->north_tex);
	if (cfg->west_tex)
		free(cfg->west_tex);
	if (cfg->east_tex)
		free(cfg->east_tex);
	if (cfg->south_tex)
		free(cfg->south_tex);
	if (cfg->floor_color)
		free(cfg->floor_color);
}
