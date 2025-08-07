/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:44:35 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/07 20:04:52 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <time.h>

/* Screen size */
# define WIDTH 1800
# define HEIGHT 1600

/* HUD */
# define MINIMAP_SCALE 15
# define MINIMAP_SIZE  10
# define MINIMAP_WALL_COLOR 0xFFFFFF88
# define MINIMAP_FLOOR_COLOR 0x00000088
# define MINIMAP_PLAYER_COLOR 0xFF0000FF
# define CHAR_COLOR 0xFFFFFF

/* Key codes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65363
# define KEY_RIGHT 65361
# define KEY_SHIFT_LEFT 65505
# define KEY_SHIFT_RIGHT 65506
# define KEY_M 109
# define KEY_F 102
# define KEY_E 101

# define KEY_MINIMAP_TOGGLE MLX_KEY_M
# define KEY_FPS_TOGGLE     MLX_KEY_F

# define TEXTURE_COUNT 5

/* Data structures */

typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
}	t_input;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	char	*door_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

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

typedef struct s_door
{
	int		x;
	int		y;
	float	open_ratio;
	int		is_opening;
}	t_door;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fps
{
	int			frames;
	int			fps;
	clock_t		last_time;
}	t_fps;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_config	*cfg;
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	t_texture	*textures[TEXTURE_COUNT];
	t_dir_info	dir_infos[4];
	t_input		input;
	int			minimap_visible;
	int			fps_visible;
	t_fps		fps;
	t_door		*doors;
	int			num_doors;
}	t_game;

/* Initialization and Config */
t_config	*mock_config(void);
int			init_game(t_game *game);
void		init_game_struct(t_game *game);
void		init_dir_infos(t_game *game);
void		init_player(t_game *game);
void		init_doors(t_game *game);

/* Door management */
int			handle_door(t_game *game, t_ray *ray);
int			handle_door_hit(t_game *game, t_ray *ray,
				t_wall *wall, int *tex_id);
void		update_doors(t_game *game);
int			find_door_index(t_game *game, int x, int y);
void		adjust_ray_for_door(t_ray *ray, float open_ratio);
void		toggle_door(t_game *game);
int			count_and_fill_doors(t_game *game);

/* Map utilities */
int			map_width(char *row);
int			map_height(char **map);
int			is_wall_or_door(t_game *game, int x, int y);
int			handle_tile(t_game *game, t_ray *ray, int map_w, int map_h);

/* Raycasting */
void		init_ray_basic(t_game *game, int x, t_ray *ray);
void		init_ray_steps(t_game *game, t_ray *ray);
int			perform_dda(t_game *game, t_ray *ray);
void		calculate_wall(t_game *game, t_ray *ray, t_wall *wall);
int			get_tex_x(t_game *game, t_ray *ray, float wall_x, int tex_id);

/* Texture management */
int			load_textures(t_game *game);
int			get_texture_index(int side, float ray_dir_x, float ray_dir_y);
int			get_texture_index_door(t_game *game, int map_x, int map_y);
int			get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y);
void		free_textures(t_game *game, int count);

/* Player movement */
void		update_player_position(t_game *game);

/* Rendering */
void		render_frame(void *param);
void		render_minimap(t_game *game);
void		render_fps(t_game *game);
void		draw_column(t_game *game, int x, t_wall *wall, t_ray *ray);

/* Fonts and text rendering */
const char	**get_font_digits(void);
const char	**get_font_letters(void);
void		draw_char(t_game *game, t_point pos,
				const char bmap[5], int scale);
void		draw_scaled_pixel(t_game *game, t_point pos,
				int scale, int color);

/* Input */
void		key_hook(mlx_key_data_t keydata, void *param);

/* Cleanup */
void		cleanup_game(t_game *game);

#endif
