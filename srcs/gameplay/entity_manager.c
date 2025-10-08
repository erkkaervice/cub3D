/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:15:47 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 17:17:36 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*upd_spr_thread(void *arg)
{
	t_sprite_thread	*t;
	int				i;
	t_sprite		*s;
	float			dx;
	float			dy;

	t = (t_sprite_thread *)arg;
	if (!t || !t->sprites)
		return (NULL);
	i = t->start;
	while (i < t->end && i < t->g->num_sprites)
	{
		s = &t->sprites[i];
		dx = s->x - t->g->player_x;
		dy = s->y - t->g->player_y;
		s->dist = dx * dx + dy * dy;
		spr_upd(t->g, s, t->dt);
		i++;
	}
	return (NULL);
}

void	start_spr_threads(t_game *g, float *zb, float dt,
		t_sprite_thread *params)
{
	pthread_t	threads[THREADS];
	int			i;
	int			chunk;

	chunk = (g->num_sprites + THREADS - 1) / THREADS;
	i = 0;
	while (i < THREADS)
	{
		params[i].g = g;
		params[i].sprites = g->sprites;
		params[i].start = i * chunk;
		params[i].end = (i + 1) * chunk;
		if (params[i].end > g->num_sprites)
			params[i].end = g->num_sprites;
		params[i].zb = zb;
		params[i].dt = dt;
		pthread_create(&threads[i], NULL, upd_spr_thread, &params[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
}

void	*spr_thread(void *arg)
{
	t_sprite_thread	*t;
	int				i;
	t_sprite		*s;

	t = (t_sprite_thread *)arg;
	if (!t || !t->sprites || !t->g || !t->g->frame || !t->zb)
		return (NULL);
	i = t->start;
	while (i < t->end && i < t->g->num_sprites)
	{
		s = &t->sprites[i];
		if (spr_project(t->g, s) && init_spr_render(t->g, s))
			spr_stripe(t->g, s, t->zb);
		i++;
	}
	return (NULL);
}

void	doors_upd(t_game *g)
{
	int	i;

	if (!g || !g->doors)
		return ;
	i = 0;
	while (i < g->num_doors)
	{
		if (g->doors[i].state == DOOR_OPENING)
			g->doors[i].open_ratio += DOOR_OPEN_SPEED;
		else if (g->doors[i].state == DOOR_CLOSING)
			g->doors[i].open_ratio -= DOOR_OPEN_SPEED;
		if (g->doors[i].state == DOOR_OPENING
			&& g->doors[i].open_ratio >= DOOR_OPEN_RATIO_FULL)
		{
			g->doors[i].open_ratio = DOOR_OPEN_RATIO_FULL;
			g->doors[i].state = DOOR_OPEN;
		}
		if (g->doors[i].state == DOOR_CLOSING
			&& g->doors[i].open_ratio <= DOOR_OPEN_RATIO_START)
		{
			g->doors[i].open_ratio = DOOR_OPEN_RATIO_START;
			g->doors[i].state = DOOR_CLOSED;
		}
		i++;
	}
}

void	door_toggle(t_game *g)
{
	int	i;
	int	x;
	int	y;

	if (!g || !g->doors)
		return ;
	x = (int)(g->player_x + g->dir_x * DOOR_TOGGLE_RANGE);
	y = (int)(g->player_y + g->dir_y * DOOR_TOGGLE_RANGE);
	i = 0;
	while (i < g->num_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
		{
			if (g->doors[i].state == DOOR_CLOSED)
				g->doors[i].state = DOOR_OPENING;
			else if (g->doors[i].state == DOOR_OPEN)
				g->doors[i].state = DOOR_CLOSING;
			break ;
		}
		i++;
	}
}
