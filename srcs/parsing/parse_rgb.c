/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:44:07 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 14:34:32 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_parse_component(const char **s)
{
	int	val;

	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (!ft_isdigit((unsigned char)**s))
		return (-1);
	val = 0;
	while (ft_isdigit((unsigned char)**s))
	{
		val = val * 10 + (**s - '0');
		if (val > 255)
			return (-1);
		(*s)++;
	}
	while (**s == ' ' || **s == '\t')
		(*s)++;
	return (val);
}

uint32_t	rgb_to_u32(const char *s)
{
	int	vals[3];
	int	idx;

	if (!s)
		return (0);
	idx = 0;
	while (idx < 3)
	{
		vals[idx] = rgb_parse_component(&s);
		if (vals[idx] < 0)
			return (0);
		idx++;
		if (*s == ',')
			s++;
		else if (idx < 3)
			return (0);
	}
	return (0xFF000000u | ((uint32_t)vals[2] << 16)
		| ((uint32_t)vals[1] << 8) | (uint32_t)vals[0]);
}

void	rgb_valid_component(char *comp, int *value, char **tokens)
{
	char	*trimmed;

	trimmed = ft_strtrim(comp, " \t\n");
	if (!trimmed || !ft_isnum(trimmed))
	{
		free(trimmed);
		free_split(tokens);
		ft_error("RGB contains non-numeric value");
	}
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (*value < 0 || *value > 255)
	{
		free_split(tokens);
		ft_error("RGB value out of range (0-255)");
	}
}

int	*rgb_parse_array(const char *color_string)
{
	int		*rgb;
	char	**tokens;
	int		count;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		ft_error("Malloc failed");
	tokens = ft_split(color_string, ',');
	if (!tokens)
		ft_error("Malloc failed");
	count = 0;
	while (tokens[count])
		count++;
	if (count != 3)
	{
		free_split(tokens);
		ft_error("RGB must have exactly 3 values");
	}
	rgb_valid_component(tokens[0], &rgb[0], tokens);
	rgb_valid_component(tokens[1], &rgb[1], tokens);
	rgb_valid_component(tokens[2], &rgb[2], tokens);
	free_split(tokens);
	return (rgb);
}
