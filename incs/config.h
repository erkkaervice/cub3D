/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:37:43 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 14:43:29 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* Window and image */
# define WINDOW_TITLE "HELLESCAPE"
# define WINDOW_IMG_POS_X 0
# define WINDOW_IMG_POS_Y 0

/* Screen dimensions */
# define WIDTH 1800
# define HEIGHT 1600

/* Colors */
# define CEILING_COLOR 0xFF003C99
# define FLOOR_COLOR 0xFF000066
# define CHAR_COLOR 0xFFFFFF

/* HUD settings */
# define MINIMAP_SCALE 15
# define MINIMAP_SIZE 10
# define MINIMAP_WALL_COLOR 0xFFFFFF88
# define MINIMAP_FLOOR_COLOR 0x00000088
# define MINIMAP_PLAYER_COLOR 0xFF0000FF

/* FPS display */
# define FPS_SCALE 5
# define FPS_POS_X 1645
# define FPS_POS_Y 8
# define FPS_LABEL "FPS:"
# define CHAR_SPACING 20

/* Key aliases */
# define KEY_MINIMAP_TOGGLE MLX_KEY_M
# define KEY_FPS_TOGGLE MLX_KEY_F

/* Movement speeds */
# define MOVE_SPEED 0.05f
# define RUN_SPEED 0.09f
# define ROT_SPEED 0.07f

/* Mouse settings */
# define MOUSE_SENSITIVITY 0.00005f
# define MOUSE_DAMPING 0.5f
# define MOUSE_DX_THRESHOLD 0.01f
# define MOUSE_START_X 900
# define MOUSE_START_Y 800
# define MOUSE_FRAME_MULTIPLIER 60.0f

/* Texture management */
# define TEXTURE_COUNT 6
# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST  2
# define TEX_EAST  3
# define TEX_DOOR  4
# define TEX_SPRITE 5

/* Texture file paths */
# define NORTH_TEXTURE_PATH "textures/north.png"
# define SOUTH_TEXTURE_PATH "textures/south.png"
# define WEST_TEXTURE_PATH  "textures/west.png"
# define EAST_TEXTURE_PATH  "textures/east.png"
# define DOOR_TEXTURE_PATH  "textures/door.png"
# define SPRITE_TEXTURE_PATH "textures/sprite.png"

/* Map tiles */
# define TILE_WALL '1'
# define TILE_DOOR 'D'

/* Sprite parameters */
# define MAX_SPRITES 100

/* Raycasting parameters */
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

/* Door parameters */
# define DOOR_OPEN_FULL 1.0f
# define DOOR_INITIAL_OPEN_RATIO 0.0f

/* Image format */
# define BYTES_PER_PIXEL 4

/* Direction information */
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

/* Player starting position and direction */
# define PLAYER_START_X 4
# define PLAYER_START_Y 3
# define PLAYER_START_DIR 'E'

#endif
