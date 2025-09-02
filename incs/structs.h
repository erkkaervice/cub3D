/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:52:20 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/01 15:40:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_game	t_game;

/* --- Basic Types --- */
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

/* --- Configuration --- */
typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	char		*door_texture;
	char		*sprite_texture_0;
	char		*sprite_texture_1;
	char		*sprite_texture_2;
	char		*floor_color;
	char		*ceiling_color;
	bool		no;
	bool		so;
	bool		we;
	bool		ea;
	bool		f;
	bool		c;
	int			player;
	char		**map;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_config;

/* --- Rendering & Textures --- */
typedef struct s_texture
{
	mlx_texture_t	*img;
	mlx_image_t		*image;
	int				width;
	int				height;
}	t_texture;

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
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	float	perp_wall_dist;
}	t_ray;

typedef struct s_wall
{
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	float	wall_x;
}	t_wall;

typedef struct s_blit
{
	t_game	*game;
	int		x;
	int		y;
	float	scale_x;
	float	scale_y;
}	t_blit;

/* --- Doors --- */
typedef struct s_door
{
	int		x;
	int		y;
	float	open_ratio;
	int		is_opening;
}	t_door;

/* --- FPS & Mouse --- */
typedef struct s_fps
{
	int			frames;
	int			fps;
	clock_t		last_time;
}	t_fps;

typedef struct s_mouse
{
	int			prev_x;
	double		dx;
	double		velocity;
	double		sensitivity;
}	t_mouse;

/* --- Sprites --- */
typedef struct s_sprite
{
	float		x;
	float		y;
	float		dist;
	int			texture_id;
	float		sx;
	float		sy;
	float		tx;
	float		ty;
	float		perp_dist;
	int			screen_x;
	int			height;
	int			width;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	t_texture	*frames[3];
	int			frame_index;
	float		anim_timer;
	float		speed;
	int			active;
	int			chasing;
	int			stopped;
}	t_sprite;

/* --- Game State --- */
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*frame;
	t_config		*cfg;
	float			player_x;
	float			player_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	t_texture		*textures[TEXTURE_COUNT];
	t_dir_info		dir_infos[DIR_COUNT];
	t_input			input;
	int				minimap_visible;
	int				fps_visible;
	t_fps			fps;
	t_door			*doors;
	int				num_doors;
	t_sprite		*sprites;
	int				num_sprites;
	t_mouse			mouse;
	float			*z_buffer;
	int				win_width;
	int				win_height;
	float			scale_x;
	float			scale_y;
	int				needs_blit;
}	t_game;

#endif
