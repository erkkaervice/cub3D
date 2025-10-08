/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:20:22 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 19:10:37 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hud_blend(t_hud px)
{
	uint32_t	*pix;
	uint32_t	c;
	float		a1;
	uint8_t		col[3];

	if (!px.dst || px.x < 0 || px.y < 0
		|| (unsigned)px.x >= (unsigned)px.frame_w
		|| (unsigned)px.y >= (unsigned)px.frame_h)
		return ;
	pix = px.dst + px.y * px.frame_w + px.x;
	c = *pix;
	a1 = 1.0f - px.alpha;
	col[0] = (uint8_t)(((px.color >> 16) & 0xFF) * px.alpha
			+ ((c >> 16) & 0xFF) * a1);
	col[1] = (uint8_t)(((px.color >> 8) & 0xFF) * px.alpha
			+ ((c >> 8) & 0xFF) * a1);
	col[2] = (uint8_t)((px.color & 0xFF) * px.alpha
			+ (c & 0xFF) * a1);
	*pix = (0xFF << 24) | (col[0] << 16) | (col[1] << 8) | col[2];
}

void	fps_str(t_game *g, t_point pos, const char *str, int scale)
{
	int	i;
	int	x;

	x = pos.x;
	i = 0;
	while (str[i] && i < FPS_MAX_CHARS)
	{
		bitmap_char(g, (t_point){x, pos.y}, str[i], scale);
		x += FPS_SPACING;
		i++;
	}
}

void	fps_num(t_fps dn)
{
	char	buf[12];
	int		len;
	int		i;
	int		tmp;

	len = 0;
	tmp = dn.value;
	if (tmp == 0)
		buf[len++] = '0';
	while (tmp > 0 && len < (int) sizeof(buf))
	{
		buf[len++] = tmp % 10 + '0';
		tmp /= 10;
	}
	i = 0;
	while (i < len / 2)
	{
		tmp = buf[i];
		buf[i] = buf[len - 1 - i];
		buf[len - 1 - i] = tmp;
		i++;
	}
	buf[len] = '\0';
	fps_str(dn.g, (t_point){dn.x, dn.y}, buf, dn.scale);
}

void	fps_draw(t_game *g)
{
	int	label_len;
	int	num_len;
	int	tmp;
	int	x;

	if (!g)
		return ;
	label_len = 0;
	while (FPS_LABEL[label_len])
		label_len++;
	tmp = g->fps.fps;
	num_len = 0;
	while (tmp > 0 || num_len == 0)
	{
		tmp /= 10;
		num_len++;
	}
	x = g->win_width - FPS_SPACING * (label_len + num_len) - 2;
	fps_str(g, (t_point){x, FPS_POS_Y}, FPS_LABEL, FPS_SCALE);
	g->fps.value = g->fps.fps;
	g->fps.x = x + FPS_SPACING * label_len;
	g->fps.y = FPS_POS_Y;
	g->fps.scale = FPS_SCALE;
	fps_num(g->fps);
}

void	fps_render(t_game *g)
{
	static double	last_update;
	double			now;

	if (!g || !g->fps_visible || !g->frame)
		return ;
	now = mlx_get_time();
	if (now - last_update >= 1.0)
	{
		g->fps.fps = g->fps.frame_count;
		g->fps.frame_count = 0;
		last_update = now;
	}
	g->fps.frame_count++;
	fps_draw(g);
}
