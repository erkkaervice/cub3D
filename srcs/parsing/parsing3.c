/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:01:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/29 17:01:51 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_is_enclosed(t_config *cfg, int i)
{
	int		j;

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
					|| j == 0 || cfg->map[i][j - 1] == ' '
					|| cfg->map[i][j - 1] == '\t')
					return (print_err(cfg, "Map is not closed", -1));
			}
			j++;
		}
		i++;
	}
	return (check_last_line(cfg->map[i]));
}

static int	read_map_lines(t_config *cfg, char *filename)
{
	int		fd;
	int		i;
	int		max_len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	max_len = 0;
	cfg->map[i] = get_next_line(fd);
	while (cfg->map[i] != NULL)
	{
		if ((int)ft_strlen(cfg->map[i]) > max_len)
			max_len = ft_strlen(cfg->map[i]);
		cfg->map[++i] = get_next_line(fd);
	}
	cfg->map[i] = NULL;
	close(fd);
	i = 0;
	while (cfg->map[i] && !is_map_line(cfg->map[i]))
		i++;
	if (!cfg->map[i] || !map_is_enclosed(cfg, i))
		return (print_err(cfg, "Error with map", -2));
	return (max_len);
}

static bool	pad_map_lines(t_config *cfg, int max_len)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (cfg->map[i])
	{
		if ((int)ft_strlen(cfg->map[i]) < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return (print_err(cfg, "Malloc failed", -1));
			j = -1;
			while (cfg->map[i][++j])
				new_line[j] = cfg->map[i][j];
			while (j < max_len)
				new_line[j++] = ' ';
			new_line[j] = '\0';
			free(cfg->map[i]);
			cfg->map[i] = new_line;
		}
		i++;
	}
	return (true);
}

static void	process_config_lines(t_config *cfg)
{
	int	i;

	i = 0;
	while (cfg->map[i])
	{
		if (is_config_line(cfg->map[i]))
			config_validation(cfg, cfg->map[i]);
		i++;
	}
}

bool	map_parsing2(t_config *cfg, char *filename)
{
	int	max_len;

	max_len = read_map_lines(cfg, filename);
	if (max_len < 0)
		return (print_err(cfg, NULL, -1));
	if (!pad_map_lines(cfg, max_len))
		return (false);
	process_config_lines(cfg);
	if (!map_validation2(cfg))
		return (false);
	return (true);
}
