/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:56:19 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 16:49:07 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_game	t_game;

/* ************************************************************************** */
/*                                    HUD                                     */
/* ************************************************************************** */

typedef struct s_hud
{
	uint32_t	*dst;
	int			frame_w;
	int			frame_h;
	int			x;
	int			y;
	uint32_t	color;
	float		alpha;
}	t_hud;

typedef struct s_fps
{
	int			frames;
	int			fps;
	int			frame_count;
	clock_t		last_time;
	t_game		*g;
	int			x;
	int			y;
	int			scale;
	int			value;
}	t_fps;

typedef struct s_mm
{
	uint32_t	*dst;
	int			frame_w;
	int			frame_h;
	int			off_x;
	int			off_y;
	int			tile_px;
	int			tx;
	int			ty;
	char		tile;
	int			cx;
	int			cy;
	float		dir_x;
	float		dir_y;
	uint32_t	color;
}	t_mm;

typedef struct s_mm_thread
{
	t_game		*g;
	int			start;
	int			end;
	uint32_t	*dst;
	int			frame_w;
	int			frame_h;
	int			off_x;
	int			off_y;
	int			tile_px;
	int			map_start;
}	t_mm_thread;

/* ************************************************************************** */
/*                                Basic Types                                 */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                                Configuration                               */
/* ************************************************************************** */
typedef struct s_config
{
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_w;
	int		map_h;

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
	char	**sprite_tex;
	char	*floor_color;
	char	*ceiling_color;

	uint32_t ceiling_color_u32;
	uint32_t floor_color_u32;
}	t_config;

/* ************************************************************************** */
/*                        Rendering & Textures                                */
/* ************************************************************************** */
typedef struct s_tex
{
	int				width;
	int				height;
	uint32_t		*pixels32;
	int				row_stride; 
	mlx_texture_t	*tex;
	mlx_image_t		*img;
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

typedef struct s_render_thread
{
	t_game *g;
	int min_x;
	int max_x;
}	t_render_thread;



typedef struct s_draw_tex
{
	t_game	*g;
	int		x;
	t_wall	*w;
	t_tex	*tex;
	int		tex_idx;
	int		shift;
}	t_draw_tex;


/* ************************************************************************** */
/*                                Sprites                                     */
/* ************************************************************************** */
typedef struct s_sprite
{
	t_tex	*frames[3];
	int		frame_index;

	float	x;
	float	y;
	float	dist;
	float	perp_dist;
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
	bool	active;
	bool	chasing;
	bool	stopped;
}	t_sprite;

typedef struct s_sprite_thread
{
	t_game		*g;
	t_sprite	*sprites;
	int			start;
	int			end;
	float		*zb;
	float		dt;
}	t_sprite_thread;

/* ************************************************************************** */
/*                                Doors                                       */
/* ************************************************************************** */
typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	float			open_ratio;
}	t_door;

/* ************************************************************************** */
/*                                FPS & Mouse                                 */
/* ************************************************************************** */


typedef struct s_mouse
{
	int		prev_x;
	double	dx;
	double	velocity;
	double	sensitivity;
}	t_mouse;

/* ************************************************************************** */
/*                                Game State                                  */
/* ************************************************************************** */
typedef struct s_game
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		move_speed;
	float		rot_speed;
	float		*z_buffer;
	int			win_width;
	int			win_height;
	mlx_image_t	*back_buffer;
	t_tex		*tex[TEX_COUNT];

	t_config	*cfg;
	t_input		input;
	bool		mm_visible;
	bool		fps_visible;
	t_fps		fps;
	t_door		*doors;
	int			num_doors;
	t_sprite	*sprites;
	int			num_sprites;
	t_mouse		mouse;

	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*front_buffer;
	mlx_image_t	*frame;

	float		scale_x;
	float		scale_y;
	int			needs_blit;
	t_dir_info	dir_infos[4];
}	t_game;

#endif
