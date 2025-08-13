/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:53:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 19:42:11 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* Initialization and Config */
t_config	*mock_config(void);
int			init_game(t_game *game);
void		init_game_struct(t_game *game);
void		init_dir_infos(t_game *game);
void		init_player(t_game *game);
void		init_doors(t_game *game);

/* Map utilities */
int			map_width(char *row);
int			map_height(char **map);
int			is_wall_or_door(t_game *game, int x, int y);
int			handle_tile(t_game *game, t_ray *ray, int map_w, int map_h);

/* Door management */
int			handle_door(t_game *game, t_ray *ray);
int			handle_door_hit(t_game *game, t_ray *ray,
				t_wall *wall, int *tex_id);
void		update_doors(t_game *game);
int			find_door_index(t_game *game, int x, int y);
void		adjust_ray_for_door(t_ray *ray, float open_ratio);
void		toggle_door(t_game *game);
int			count_and_fill_doors(t_game *game);

/* Raycasting */
void		init_ray_basic(t_game *game, int x, t_ray *ray);
void		init_ray_steps(t_game *game, t_ray *ray);
int			perform_dda(t_game *game, t_ray *ray, int x);
void		calculate_wall(t_game *game, t_ray *ray, t_wall *wall);

/* Texture management */
int			get_tex_x(t_game *game, t_ray *ray, float wall_x, int tex_id);
int			load_textures(t_game *game);
int			get_texture_index(int side, float ray_dir_x, float ray_dir_y);
int			get_texture_index_door(t_game *game, int map_x, int map_y);
int			get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y);
void		free_textures(t_game *game, int count);

/* Player movement */
void		update_player_position(t_game *game);

/* Input */
void		key_hook(mlx_key_data_t keydata, void *param);

/* Mouse input */
void		mouse_init(t_game *game);
void		mouse_move(double x, double y, void *param);
void		apply_mouse_look(t_game *game, double frame_time);

/* Rendering */
void		render_frame(void *param);
void		render_minimap(t_game *game);
void		render_fps(t_game *game);

/* Sprites */
void		init_sprite(t_sprite *s, int x, int y);
void		parse_sprites(t_game *game);
void		render_sprites(t_game *game, float *z_buffer);
void		init_sprite_render(t_game *g, t_sprite *s);
void		draw_sprite_stripe(t_game *g, t_sprite *s, float *zb);

/* Fonts and text rendering */
const char	**get_font_digits(void);
const char	**get_font_letters(void);
void		draw_char(t_game *game, t_point pos,
				const char bmap[5], int scale);
void		draw_scaled_pixel(t_game *game, t_point pos,
				int scale, int color);

/* Cleanup */
void		cleanup_game(t_game *game);

#endif
