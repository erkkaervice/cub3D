/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:53:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/02 20:10:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* ************************************************************************** */
/*                        Initialization & Config                             */
/* ************************************************************************** */
t_config	*map_config(char *f);
int			init_game(t_game *g, char *f);
void		init_game_struct(t_game *g);
void		init_dir_infos(t_game *g);
void		init_player(t_game *g);
void		init_doors(t_game *g);
void		init_mouse(t_game *g);

/* ************************************************************************** */
/*                         Map utilities & validation                         */
/* ************************************************************************** */
void		file_valid(char *f, char *ext1, char *ext2);
int			map_dim(char **map, int mode);
int			is_wall_or_door(t_game *g, int x, int y);
int			handle_tile(t_game *g, t_ray *r, int map_w, int map_h);
bool		validate_player(t_config *cfg, int map_start);
bool		map_parsing(t_config *cfg, char *f);
bool		map_parsing2(t_config *cfg, char *f);
bool		map_validation2(t_config *cfg);
bool		map_validation3(t_config *cfg);
void		config_validation(t_config *cfg, char *line);
void		set_path(char **dest, bool *seen, char *line, t_config *cfg);
uint32_t	color_converter(int *rgb);
int			*color_atoia(const char *color_string);
bool		process_config_lines2(t_config *cfg, int *i,
				int *config_count, bool *map_started);

/* ************************************************************************** */
/*                          Parsing utilities                                 */
/* ************************************************************************** */
bool		is_map_line(char *line);
bool		is_config_line(char *line);
bool		is_empty_line(char *line);
int			print_err(t_config *cfg, char *line, int fd);
void		free_cfg_tex(t_config *cfg);

/* ************************************************************************** */
/*                               Cleanup                                      */
/* ************************************************************************** */
void		cleanup_game(t_game *g);
void		cleanup_cfg_tex_paths(t_config *cfg);
void		free_partial_config(t_config **cfg_ptr);

/* ************************************************************************** */
/*                               Raycasting                                   */
/* ************************************************************************** */
void		init_ray_basic(t_game *g, int x, t_ray *r);
void		init_ray_steps(t_game *g, t_ray *r);
int			perform_dda(t_game *g, t_ray *r, int x);
void		calculate_wall(t_game *g, t_ray *r, t_wall *w);
void		raycast_column(t_game *g, int x);

/* ************************************************************************** */
/*                               Rendering                                    */
/* ************************************************************************** */
void		draw_column(t_game *g, t_wall *w, int x, int tex_id);
void		blend_pixel(uint32_t *dst, uint32_t src, float *zbuf, float dist);
void		blit_scaled(t_game *g);
void		render_frame(void *param);
void		render_minimap(t_game *g);
void		render_fps(t_game *g);

/* ************************************************************************** */
/*                             Texture management                             */
/* ************************************************************************** */
int			load_tex(t_game *g);
int			get_tex_index(int side, float ray_dir_x, float ray_dir_y);
int			get_tex_index_door(t_game *g, int map_x, int map_y);
int			get_tex_x(t_game *g, t_ray *r, float wall_x, int tex_id);
int			get_tex_color_from_tex(t_tex *tex, int tex_x, int tex_y);
int			get_tex_color(t_game *g, int tex_id, int tex_x, int tex_y);
void		free_tex(t_game *g, int count);

/* ************************************************************************** */
/*                              Door management                               */
/* ************************************************************************** */
int			count_doors(t_game *g);
int			fill_doors(t_game *g);
int			count_and_fill_doors(t_game *g);
int			find_door_index(t_game *g, int x, int y);
int			handle_door(t_game *g, t_ray *r);
int			door_hit(t_game *g, t_ray *r, t_wall *w, int *tex_id);
void		update_doors(t_game *g);
void		adjust_ray_for_door(t_ray *r, float open_ratio);
void		toggle_door(t_game *g);

/* ************************************************************************** */
/*                        Player movement & Input                             */
/* ************************************************************************** */
int			can_move(t_game *g, float x, float y);
void		update_player_position(t_game *g);
void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_init(t_game *g);
void		mouse_move(double x, double y, void *param);
void		apply_mouse_look(t_game *g, double frame_time);

/* ************************************************************************** */
/*                                 Sprites                                    */
/* ************************************************************************** */
void		init_sprite(t_game *g, t_sprite *s, int x, int y);
int			init_sprite_render(t_game *g, t_sprite *s);
void		parse_sprites(t_game *g);
int			compute_sprite_transform(t_game *g, t_sprite *s);
void		compute_sprite_bounds(t_game *g, t_sprite *s);
void		draw_sprite_stripe(t_game *g, t_sprite *s, float *zb);
void		render_sprites(t_game *g, float *zb);
void		update_sprite(t_game *g, t_sprite *s, float dt);
void		update_sprite_behavior(t_game *g, t_sprite *s, float dt);

/* ************************************************************************** */
/*                           Fonts & text rendering                           */
/* ************************************************************************** */
const char	**get_font_digits(void);
const char	**get_font_letters(void);
void		draw_scaled_pixel(t_game *g, t_point pos, int scale, int color);
void		draw_char(t_game *g, t_point pos, const char bmap[5], int scale);

#endif
