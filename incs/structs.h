/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:52:20 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 18:00:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_game	t_game;

/* ========================================================================== */
/*                                BASIC TYPES                                 */
/* ========================================================================== */

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_input
{
	int	move_forward;
	int	move_backward;
	int	move_left;
	int	move_right;
	int	rotate_left;
	int	rotate_right;
	int	run;
	int	interact;
	int	minimap_toggle;
	int	fps_toggle;
}	t_input;

/* ========================================================================== */
/*                              CONFIGURATION                                 */
/* ========================================================================== */

typedef struct s_config
{
	int		player;
	int		player_x;
	int		player_y;
	char	player_dir;
	char	**map;
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
	char	*north_tex;
	char	*south_tex;
	char	*east_tex;
	char	*west_tex;
	char	*door_tex;
	char	*sprite_tex_0;
	char	*sprite_tex_1;
	char	*sprite_tex_2;
	char	*floor_color;
	char	*ceiling_color;
}	t_config;

/* ========================================================================== */
/*                          RENDERING & TEXTURES                              */
/* ========================================================================== */

typedef struct s_tex
{
	int				width;
	int				height;
	mlx_texture_t	*img;
	mlx_image_t		*image;
}	t_tex;

typedef struct s_dir_info
{
	char	dir;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_dir_info;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
}	t_ray;

typedef struct s_wall
{
	float	perp_wall_dist;
	float	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_wall;

typedef struct s_blit
{
	t_game	*game;
	int		x;
	int		y;
	float	scale_x;
	float	scale_y;
}	t_blit;

/* ========================================================================== */
/*                                   DOORS                                    */
/* ========================================================================== */

typedef struct s_door
{
	int		x;
	int		y;
	float	open_ratio;
	int		is_opening;
}	t_door;

/* ========================================================================== */
/*                               FPS & MOUSE                                  */
/* ========================================================================== */

typedef struct s_fps
{
	int		frames;
	int		fps;
	clock_t	last_time;
}	t_fps;

typedef struct s_mouse
{
	int		prev_x;
	double	dx;
	double	velocity;
	double	sensitivity;
}	t_mouse;

/* ========================================================================== */
/*                                  SPRITES                                   */
/* ========================================================================== */

typedef struct s_sprite
{
	int		tex_id;
	t_tex	*frames[3];
	int		frame_index;

	float	x;
	float	y;
	float	dist;
	float	perp_dist;
	float	sx;
	float	sy;
	float	tx;
	float	ty;

	int		screen_x;
	int		height;
	int		width;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;

	float	anim_timer;
	float	speed;
	int		active;
	int		chasing;
	int		stopped;
}	t_sprite;

/* ========================================================================== */
/*                                GAME STATE                                  */
/* ========================================================================== */

typedef struct s_game
{
	t_config	*cfg;

	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;

	t_tex		*tex[TEX_COUNT];
	t_dir_info	dir_infos[DIR_COUNT];

	t_input		input;

	int			win_width;
	int			win_height;
	int			minimap_visible;
	int			fps_visible;

	t_fps		fps;

	t_door		*doors;
	int			num_doors;

	t_sprite	*sprites;
	int			num_sprites;

	t_mouse		mouse;

	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*frame;

	float		*z_buffer;
	float		scale_x;
	float		scale_y;
	int			needs_blit;
}	t_game;

#endif
