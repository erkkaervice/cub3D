/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:43:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 13:52:38 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_count_lines(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Cannot open map file");
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	map_fill_lines(t_config *cfg, const char *filename)
{
	int		fd;
	int		i;
	int		max_len;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Cannot open map file");
	i = 0;
	max_len = 0;
	line = get_next_line(fd);
	while (line)
	{
		cfg->map[i] = line;
		if ((int)ft_strlen(line) > max_len)
			max_len = ft_strlen(line);
		i++;
		line = get_next_line(fd);
	}
	cfg->map[i] = NULL;
	close(fd);
	return (max_len);
}

bool	map_is_line(const char *line)
{
	bool	has_map_char;

	has_map_char = false;
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || *line == 'D' || *line == 'X')
			has_map_char = true;
		else if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (has_map_char);
}

int	map_valid_enc(t_config *cfg, int i)
{
	int	j;

	while (cfg->map[i + 1])
	{
		j = 0;
		while (cfg->map[i][j])
		{
			while (cfg->map[i][j] == ' ' || cfg->map[i][j] == '\t')
				j++;
			if (cfg->map[i][j] == '0')
			{
				if (cfg->map[i][j + 1] == '\0' || cfg->map[i][j + 1] == ' '
					|| cfg->map[i][j + 1] == '\n' || cfg->map[i][j + 1] == '\t'
					|| cfg->map[i - 1][j] == '\0' || cfg->map[i + 1][j] == '\0'
					|| cfg->map[i - 1][j] == ' ' || cfg->map[i + 1][j] == ' '
					|| cfg->map[i + 1][j] == '\n' || cfg->map[i - 1][j] == '\n'
					|| j == 0 || cfg->map[i][j - 1] == ' ')
					ft_error("Map is not closed");
			}
			j++;
		}
		i++;
	}
	map_check_last_line(cfg->map[i]);
	return (1);
}

int	map_check_last_line(char *last_line)
{
	int	i;

	i = 0;
	while (last_line[i])
	{
		if (last_line[i] == '0')
			ft_error("Map is not closed");
		i++;
	}
	return (1);
}
