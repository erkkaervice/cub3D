/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:53:05 by eala-lah          #+#    #+#             */
/*   Updated: 2025/10/08 19:18:35 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# ifndef CUB3D_H
#  error "Include cub3d.h before functions.h"
# endif

/*freedom*/
void		free_game(t_game *g);
void		free_cfg(t_config **cfg_ptr);
void		free_tex(t_game *g);
void		free_cfg_tex(t_config *cfg);
void		free_split(char **split);

/*parsing*/
void		cfg_check_file(char *filename, char *ext1, char *ext2);
void		cfg_set_asset(char **dest, bool *seen, char *line);
int			map_load(t_config *cfg, const char *filename);
bool		map_normalize(t_config *cfg, int max_len);
void		map_valid_struct(t_config *cfg, int start_line);
void		init_spr(t_game *g, t_sprite *s, int x, int y);
int			*rgb_parse_array(const char *color_string);
bool		cfg_is_line(const char *line);
bool		map_valid_player(t_config *cfg, int map_start);
int			map_check_last_line(char *last_line);
void		cfg_parse_line(t_config *cfg, char *line);

/*initialisation*/
void		init_struct(t_game *g);
int			init_resources(t_game *g, const char *f);
int			init_game(t_game *g, const char *f);
t_config	*world_config(const char *f);
int			tex_load_all(t_game *g);
void		spr_parse(t_game *g);
void		doors_init(t_game *g);
int			spr_reset(t_game *g);
int			init_mlx(t_game *g);
void		cleanup_game(t_game *g);
void		init_mouse(t_game *g);
void		mouse_move(double x, double y, void *param);
void		init_dirs(t_game *g);
void		init_player(t_game *g);
void		key_input(mlx_key_data_t keydata, void *param);
void		app_close(void *param);
void		draw_frame(void *param);
void		resize_buffers(int32_t w, int32_t h, void *param);
void		spr_bounds(t_game *g, t_sprite *s);
void		init_fps(t_fps *fps, t_game *g);
bool		cfg_parse(t_config *cfg, const char *filename);
uint32_t	rgb_to_u32(const char *s);
int			map_count_lines(const char *filename);
int			map_fill_lines(t_config *cfg, const char *filename);
bool		map_is_line(const char *line);
int			map_valid_enc(t_config *cfg, int i);

/*raycasting*/
int			map_dim(char **map, int mode);
void		init_ray(const t_game *g, int x, t_ray *ray);
void		init_ray_steps(const t_game *g, t_ray *ray);
void		door_draw_col(t_game *g, t_ray *r, int x);
void		draw_wall(t_game *g, t_ray *r, int x);
int			raycast_dda(const t_game *g, t_ray *r, int x);
void		wall_calc_bounds(const t_game *g, const t_ray *r, t_wall *w);
int			wall_tex_idx(int side, float ray_dir_x, float ray_dir_y);
int			wall_tex_x(const t_game *g, const t_ray *r,
				float wall_x, int tex_id);
void		draw_tex(t_draw_tex args);
void		spr_render(t_game *g, float *zb, float dt);
void		mm_render(t_game *g);
void		fps_render(t_game *g);
void		raycast_column(t_game *g, int x);
void		clear_frame(t_game *g);
void		doors_upd(t_game *g);
void		mouse_look(t_game *g, double frame_time);
void		update_pos(t_game *g);
void		copy_back(t_game *g);
t_tex		*col_validate(t_game *g, t_wall *w, int x, int tex_id);
uint32_t	tex_color(const t_game *g, int tex_id, int tex_x, int tex_y);

/*sprites*/
void		spr_upd(t_game *g, t_sprite *s, float dt);
void		blend(uint32_t *restrict dst, uint32_t src,
				float *restrict zbuf, float dist);
int			tex_pixel(const t_tex *t, int tex_x, int tex_y);
int			spr_project(t_game *g, t_sprite *s);
int			init_spr_render(t_game *g, t_sprite *s);
void		spr_stripe(t_game *g, t_sprite *s, float *zb);
void		*spr_thread(void *arg);
void		start_spr_threads(t_game *g, float *zb, float dt,
				t_sprite_thread *params);
void		sort_spr(t_game *g);
int			can_move(const t_game *g, float x, float y);
int			spr_los(const t_game *g, t_sprite *s);

/*doors*/
int			door_idx(const t_game *g, int x, int y);
void		door_toggle(t_game *g);
int			tile_blocked(const t_game *g, int x, int y);
void		hud_blend(t_hud px);

/*HUD*/
void		bitmap_char(t_game *g, t_point pos, char c, int scale);
void		init_mm(t_game *g, uint32_t *dst, int *v, t_mm_thread *p);
void		spr_normalize(float *fx, float *fy);
void		mm_threads(t_game *g, int *v);
void		mm_player(t_game *g, int *v);
void		mm_sprites(t_game *g, int *v);

#endif
