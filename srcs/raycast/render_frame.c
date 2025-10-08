/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:09:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/07 15:28:43 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_overlays(t_game *g, float dt)
{
	if (!g || !g->frame || !g->z_buffer)
		return ;
	spr_render(g, g->z_buffer, dt);
	if (g->mm_visible)
		mm_render(g);
	if (g->fps_visible)
		fps_render(g);
}

void	*col_draws(void *arg)
{
	t_render_thread	*rt;
	t_game			*g;
	int				x;

	rt = (t_render_thread *)arg;
	g = rt->g;
	x = rt->min_x - 1;
	while (++x <= rt->max_x)
		raycast_column(g, x);
	return (NULL);
}

void	col_draws_mt(t_game *g)
{
	const int		thread_count = 4;
	pthread_t		threads[4];
	t_render_thread	args[4];
	int				slice;
	int				i;

	slice = g->win_width / thread_count;
	i = -1;
	while (++i < thread_count)
	{
		args[i].g = g;
		args[i].min_x = i * slice;
		if (i == thread_count - 1)
			args[i].max_x = g->win_width - 1;
		else
			args[i].max_x = (i + 1) * slice - 1;
		pthread_create(&threads[i], NULL, col_draws, &args[i]);
	}
	i = -1;
	while (++i < thread_count)
		pthread_join(threads[i], NULL);
}

void	draw_frame(void *param)
{
	static double	last_time = 0.0;
	t_game			*g;
	double			current_time;
	double			frame_time;

	g = (t_game *)param;
	if (!g)
		return ;
	current_time = mlx_get_time();
	frame_time = current_time - last_time;
	last_time = current_time;
	g->frame = g->back_buffer;
	clear_frame(g);
	doors_upd(g);
	mouse_look(g, frame_time);
	update_pos(g);
	col_draws_mt(g);
	draw_overlays(g, (float)frame_time);
	copy_back(g);
	g->frame = g->front_buffer;
	g->needs_blit = 0;
}

void	clear_frame(t_game *g)
{
	int			i;
	int			total;
	int			half;
	uint32_t	*pixels;

	if (!g || !g->z_buffer || !g->back_buffer || !g->back_buffer->pixels
		|| !g->cfg)
		return ;
	i = -1;
	while (++i < g->win_width)
		g->z_buffer[i] = INFINITY;
	pixels = (uint32_t *)g->back_buffer->pixels;
	total = g->back_buffer->width * g->back_buffer->height;
	half = total / 2;
	i = 0;
	while (i < half)
	{
		pixels[i] = g->cfg->ceiling_color_u32;
		i++;
	}
	while (i < total)
	{
		pixels[i] = g->cfg->floor_color_u32;
		i++;
	}
}
