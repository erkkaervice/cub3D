/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:37:43 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/25 18:23:18 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ************************************************************************** */
/*                               WINDOW SETTINGS                              */
/* ************************************************************************** */
# define WINDOW_TITLE "HELLESCAPE"
# define WINDOW_IMG_POS_X 0
# define WINDOW_IMG_POS_Y 0
# define WIDTH 1800
# define HEIGHT 1600

/* ************************************************************************** */
/*                               COLORS SETTINGS                              */
/* ************************************************************************** */
# define CHAR_COLOR 0xFFFFFF

/* ************************************************************************** */
/*                               HUD SETTINGS                                 */
/* ************************************************************************** */
# define MINIMAP_SCALE 15
# define MINIMAP_SIZE 10
# define MINIMAP_WALL_COLOR 0xFFFFFF88
# define MINIMAP_FLOOR_COLOR 0x00000088
# define MINIMAP_PLAYER_COLOR 0xFF0000FF
# define MINIMAP_DOOR_COLOR 0xFF00FF00
# define MINIMAP_SPRITE_COLOR 0xFFFF00FF

/* FPS display */
# define FPS_SCALE 5
# define FPS_POS_X 1645
# define FPS_POS_Y 8
# define FPS_LABEL "FPS:"
# define CHAR_SPACING 20

/* ************************************************************************** */
/*                               KEY SETTINGS                                 */
/* ************************************************************************** */
# define KEY_MINIMAP_TOGGLE MLX_KEY_M
# define KEY_FPS_TOGGLE MLX_KEY_F

/* ************************************************************************** */
/*                               PLAYER SETTINGS                              */
/* ************************************************************************** */
# define PLAYER_START_X 4
# define PLAYER_START_Y 3
# define PLAYER_START_DIR 'E'

/* Movement speeds */
# define MOVE_SPEED 0.05f
# define RUN_SPEED 0.09f
# define ROT_SPEED 0.07f

/* ************************************************************************** */
/*                               MOUSE SETTINGS                               */
/* ************************************************************************** */
# define MOUSE_SENSITIVITY 0.00005f
# define MOUSE_DAMPING 0.5f
# define MOUSE_DX_THRESHOLD 0.01f
# define MOUSE_START_X 900
# define MOUSE_START_Y 800
# define MOUSE_FRAME_MULTIPLIER 60.0f

/* ************************************************************************** */
/*                               TEXTURE SETTINGS                             */
/* ************************************************************************** */
# define TEXTURE_COUNT 6
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3
# define TEX_DOOR  4
# define TEX_SPRITE 5

# define DOOR_TEXTURE_PATH  "textures/door.png"
# define SPRITE_TEXTURE_PATH "textures/sprite.png"

/* ************************************************************************** */
/*                               MAP ELEMENTS SETTINGS                        */
/* ************************************************************************** */
# define TILE_WALL '1'
# define TILE_DOOR 'D'
# define TILE_SPRITE 'X'
# define TILE_FLOOR '0'
# define TILE_SPAWN 'W'

# define MAX_SPRITES 100
# define MAX_DOORS 50

/* ************************************************************************** */
/*                               SPRITE SETTINGS                              */
/* ************************************************************************** */
# define SPRITE_DEFAULT_SCALE 1.0f
# define SPRITE_DEFAULT_COLOR 0xFFFFFFFF

/* ************************************************************************** */
/*                               RAYCASTING SETTINGS                          */
/* ************************************************************************** */
# define MAX_DDA_STEPS 1000
# define AXIS_X 0
# define AXIS_Y 1
# define RAY_MAX_DIST 1e30f
# define MIN_PERP_DIST 0.001f
# define HALF_TILE_OFFSET 0.5f

/* Hit detection results */
# define HIT_NONE 0
# define HIT_WALL 1
# define HIT_DOOR 2

/* ************************************************************************** */
/*                               DOOR SETTINGS                                */
/* ************************************************************************** */
# define DOOR_OPEN_FULL 1.0f
# define DOOR_INITIAL_OPEN_RATIO 0.0f

/* ************************************************************************** */
/*                               IMAGE FORMAT                                 */
/* ************************************************************************** */
# define BYTES_PER_PIXEL 4

/* ************************************************************************** */
/*                               DIRECTION SETTINGS                           */
/* ************************************************************************** */
# define DIR_COUNT 4

# define DIR_NORTH 'N'
# define DIR_SOUTH 'S'
# define DIR_EAST  'E'
# define DIR_WEST  'W'

# define DIR_NORTH_X 0
# define DIR_NORTH_Y -1
# define DIR_NORTH_PLANE_X 0.66f
# define DIR_NORTH_PLANE_Y 0

# define DIR_SOUTH_X 0
# define DIR_SOUTH_Y 1
# define DIR_SOUTH_PLANE_X -0.66f
# define DIR_SOUTH_PLANE_Y 0

# define DIR_EAST_X 1
# define DIR_EAST_Y 0
# define DIR_EAST_PLANE_X 0
# define DIR_EAST_PLANE_Y 0.66f

# define DIR_WEST_X -1
# define DIR_WEST_Y 0
# define DIR_WEST_PLANE_X 0
# define DIR_WEST_PLANE_Y -0.66f

#endif
