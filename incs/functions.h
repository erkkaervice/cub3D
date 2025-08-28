/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:53:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/28 17:54:14 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// --- Raycasting ---
void		init_ray_basic(t_game *game, int x, t_ray *ray);
void		init_ray_steps(t_game *game, t_ray *ray);
int			perform_dda(t_game *game, t_ray *ray, int x);
void		calculate_wall(t_game *game, t_ray *ray, t_wall *wall);

// --- Rendering ---
void		blend_write_pixel(uint32_t *dst, uint32_t src,
				float *zbuf, float dist);
void		render_frame(void *param);
void		render_sprites(t_game *game, float *z_buffer);
void		init_sprite_render(t_game *g, t_sprite *s);
void		draw_sprite_stripe(t_game *g, t_sprite *s, float *zb);
void		render_minimap(t_game *game);
void		render_fps(t_game *game);

// --- Player movement & Input ---
void		update_player_position(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_init(t_game *game);
void		mouse_move(double x, double y, void *param);
void		apply_mouse_look(t_game *game, double frame_time);

// --- Door management ---
int			handle_door(t_game *game, t_ray *ray);
int			door_hit(t_game *game, t_ray *ray, t_wall *wall, int *tex_id);
void		update_doors(t_game *game);
void		adjust_ray_for_door(t_ray *ray, float open_ratio);
void		toggle_door(t_game *game);
int			count_doors(t_game *game);
int			fill_doors(t_game *game);
int			count_and_fill_doors(t_game *game);
int			find_door_index(t_game *game, int x, int y);

// --- Texture management ---
int			get_tex_x(t_game *game, t_ray *ray, float wall_x, int tex_id);
int			load_textures(t_game *game);
int			get_texture_index(int side, float ray_dir_x, float ray_dir_y);
int			get_texture_index_door(t_game *game, int map_x, int map_y);
int			get_texture_color(t_game *game, int tex_id, int tex_x, int tex_y);
void		free_textures(t_game *game, int count);

// --- Sprites ---
void		init_sprite(t_sprite *s, int x, int y);
void		parse_sprites(t_game *game);

// --- Fonts & text rendering ---
const char	**get_font_digits(void);
const char	**get_font_letters(void);
void		draw_char(t_game *game, t_point pos, const char bmap[5], int scale);
void		draw_scaled_pixel(t_game *game, t_point pos, int scale, int color);

// --- Initialization & Config ---
t_config	*mock_config(char *filename);
int			init_game(t_game *game, char *filename);
void		init_game_struct(t_game *game);
void		init_dir_infos(t_game *game);
void		init_player(t_game *game);
void		init_doors(t_game *game);

// --- Map utilities ---
int			map_width(char *row);
int			map_height(char **map);
int			is_wall_or_door(t_game *game, int x, int y);
int			handle_tile(t_game *game, t_ray *ray, int map_w, int map_h);

// --- Map parsing & validation ---
void		file_valid(char *filename, char *ext1, char *ext2);
bool		map_parsing(t_config *cfg, char *filename);
bool		map_parsing2(t_config *cfg, char *filename);
void		config_validation(t_config *cfg, char *config_line);
bool		map_validation2(t_config *cfg);
bool		map_validation3(t_config *cfg);
bool		validate_player(t_config *cfg, int map_start);
void		set_path(char **dest, bool *seen, char *line, t_config *cfg);
uint32_t	color_converter(int *rgb);
int			*color_atoia(const char *color_string);

// --- Parsing utils ---
bool		is_map_line(char *line);
bool		is_config_line(char *line);
bool		is_empty_line(char *line);
int			print_err(t_config *cfg, char *error, int fd);
void		free_partial_config(t_config *cfg);
void		free_cfg_textures(t_config *cfg);

// --- Cleanup ---
void		cleanup_game(t_game *game);
void		cleanup_cfg_textures_paths(t_config *cfg);

#endif
