/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:25:54 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/09 15:02:39 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_input *input, int key, int value)
{
	if (key == KEY_MOVE_FORWARD)
		input->move_forward = value;
	else if (key == KEY_MOVE_BACKWARD)
		input->move_backward = value;
	else if (key == KEY_MOVE_LEFT)
		input->move_left = value;
	else if (key == KEY_MOVE_RIGHT)
		input->move_right = value;
	else if (key == KEY_ROTATE_LEFT)
		input->rotate_left = value;
	else if (key == KEY_ROTATE_RIGHT)
		input->rotate_right = value;
	else if (key == KEY_RUN)
		input->run = value;
	else if (key == KEY_INTERACT)
		input->interact = value;
	else if (key == KEY_MM_TOGGLE)
		input->minimap_toggle = value;
	else if (key == KEY_FPS_TOGGLE)
		input->fps_toggle = value;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(g->mlx);
		else if (keydata.key == KEY_MM_TOGGLE)
			g->minimap_visible = !g->minimap_visible;
		else if (keydata.key == KEY_FPS_TOGGLE)
			g->fps_visible = !g->fps_visible;
		else if (keydata.key == KEY_INTERACT)
			toggle_door(g);
		else
			set_key(&g->input, keydata.key, 1);
	}
	else if (keydata.action == MLX_RELEASE)
		set_key(&g->input, keydata.key, 0);
}

void	mouse_move(double x, double y, void *param)
{
	t_game	*g;
	double	diff;
	int		center_x;
	int		center_y;

	(void)y;
	g = (t_game *)param;
	if (!g || !g->frame)
		return ;
	center_x = g->frame->width / 2;
	center_y = g->frame->height / 2;
	diff = x - g->mouse.prev_x;
	g->mouse.dx += diff;
	g->mouse.prev_x = center_x;
	mlx_set_mouse_pos(g->mlx, center_x, center_y);
}

void	apply_mouse_look(t_game *g, double frame_time)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	if (g->mouse.dx != 0.0)
	{
		rot = (g->mouse.dx * g->mouse.sensitivity) * frame_time
			* MOUSE_FRAME_MULTIPLIER;
		old_dir_x = g->dir_x;
		old_plane_x = g->plane_x;
		g->dir_x = g->dir_x * cos(rot) - g->dir_y * sin(rot);
		g->dir_y = old_dir_x * sin(rot) + g->dir_y * cos(rot);
		g->plane_x = g->plane_x * cos(rot) - g->plane_y * sin(rot);
		g->plane_y = old_plane_x * sin(rot) + g->plane_y * cos(rot);
		g->mouse.dx *= MOUSE_DAMPING;
		if (fabs(g->mouse.dx) < MOUSE_DX_THRESHOLD)
			g->mouse.dx = 0.0;
	}
}
