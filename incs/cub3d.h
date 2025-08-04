/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:24:31 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/04 17:23:25 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>

/* Screen & Key Constants */
# define WIDTH 1800
# define HEIGHT 1600
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

/* Input State */
typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_input;

/* Parsed Config */
typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

/* Texture Data */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture;

/* Initial Dir Setup (for N/S/W/E) */
typedef struct s_dir_info
{
	char	dir;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_dir_info;

/* Raycasting Data */
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
}	t_ray;

/* Wall Hit Info */
typedef struct s_wall
{
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_wall;

/* Main Game Struct */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_config	*cfg;
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	t_texture	*textures[4];
	t_dir_info	dir_infos[4];
	t_input		input;
}	t_game;

/* Init */
void		init_game_struct(t_game *game);
void		init_dir_infos(t_game *game);
void		init_player(t_game *game);
t_config	*mock_config(void);
int			init_game(t_game *game);

/* Rendering */
int			render_frame(void *param);
void		draw_column(t_game *game, int x, t_wall *wall, t_ray *ray);
int			get_tex_x(t_game *game, t_ray *ray, float wall_x);
void		raycast(t_game *game);
void		update_player_position(t_game *game);

/* Textures */
int			load_texture(void *mlx, t_texture *texture, char *path);
int			load_textures(t_game *game);
int			get_texture_index(int side, float ray_dir_x, float ray_dir_y);
int			get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y);
void		free_textures(t_game *game, int count);

/* Input */
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

/* Utils */
int			map_height(char **map);
int			map_width(char *row);
void		cleanup_game(t_game *game);

#endif
