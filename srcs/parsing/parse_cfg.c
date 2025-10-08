/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cfg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:43:45 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 13:50:39 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	cfg_is_line(const char *line)
{
	while (ft_isspace(*line))
		line++;
	return (ft_strncmp("NO ", line, 3) == 0
		|| ft_strncmp("SO ", line, 3) == 0
		|| ft_strncmp("WE ", line, 3) == 0
		|| ft_strncmp("EA ", line, 3) == 0
		|| ft_strncmp("F ", line, 2) == 0
		|| ft_strncmp("C ", line, 2) == 0);
}

void	cfg_parse_line(t_config *cfg, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp("NO ", line, 3) == 0)
		cfg_set_asset(&cfg->north_tex, &cfg->no, line);
	else if (ft_strncmp("WE ", line, 3) == 0)
		cfg_set_asset(&cfg->west_tex, &cfg->we, line);
	else if (ft_strncmp("EA ", line, 3) == 0)
		cfg_set_asset(&cfg->east_tex, &cfg->ea, line);
	else if (ft_strncmp("SO ", line, 3) == 0)
		cfg_set_asset(&cfg->south_tex, &cfg->so, line);
	else if (ft_strncmp("F ", line, 2) == 0)
		cfg_set_asset(&cfg->floor_color, &cfg->f, line);
	else if (ft_strncmp("C ", line, 2) == 0)
		cfg_set_asset(&cfg->ceiling_color, &cfg->c, line);
}

void	cfg_set_asset(char **dest, bool *seen, char *line)
{
	if (*seen)
		ft_error("Duplicate asset");
	*seen = true;
	*dest = ft_strtrim(ft_strchr(line, ' '), " \t\n");
}

void	cfg_check_file(char *filename, char *ext1, char *ext2)
{
	int	len;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Invalid file");
	close(fd);
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ext1, 4)
		|| !ft_strncmp(filename + len - 5, ext2, 5))
		ft_error("Invalid file!");
}

bool	cfg_parse(t_config *cfg, const char *filename)
{
	int	i;
	int	max_len;

	max_len = map_load(cfg, filename);
	map_normalize(cfg, max_len);
	i = 0;
	while (cfg->map[i])
	{
		if (cfg_is_line(cfg->map[i]))
			cfg_parse_line(cfg, cfg->map[i]);
		i++;
	}
	map_valid_struct(cfg, 0);
	return (true);
}
