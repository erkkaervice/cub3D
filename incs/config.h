/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:37:43 by eala-lah          #+#    #+#             */
/*   Updated: 2025/09/04 17:45:00 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ========================================================================== */
/*                                WINDOW                                      */
/* ========================================================================== */
# define WINDOW_TITLE               "NOT TODAY SATAN!"
# define WINDOW_WIDTH               1800
# define WINDOW_HEIGHT              1600
# define BYTES_PER_PIXEL            4

/* ========================================================================== */
/*                                HUD & OVERLAYS                              */
/* ========================================================================== */
# define MM_SCALE                   15
# define MM_RADIUS                  10
# define MM_WALL_COLOR              0xFFFFFF88
# define MM_FLOOR_COLOR             0x00000088
# define MM_PLAYER_COLOR            0xFF0000FF
# define MM_DOOR_COLOR              0xFF00FF00
# define MM_SPRITE_COLOR            0xFFFF00FF

# define FPS_SCALE                  5
# define FPS_POS_Y                  8
# define FPS_POS_X                  8
# define FPS_LABEL                  "FPS:"
# define FPS_CHAR_COLOR             0xFFFFFF
# define FPS_CHAR_SPACING           20
# define FONT_ROWS                  5
# define FONT_COLS                  3
# define FONT_DIGITS_COUNT          10
# define FONT_LETTERS_COUNT         3

/* ========================================================================== */
/*                                INPUT & MOUSE                               */
/* ========================================================================== */
# define MOUSE_SENSITIVITY          0.00005f
# define MOUSE_DAMPING              0.5f
# define MOUSE_DX_THRESHOLD         0.01f
# define MOUSE_FRAME_MULTIPLIER     60.0f
# define MOUSE_MODE_HIDDEN          MLX_MOUSE_HIDDEN

/* ========================================================================== */
/*                                KEY BINDINGS                                */
/* ========================================================================== */
# define KEY_MOVE_FORWARD           MLX_KEY_W
# define KEY_MOVE_BACKWARD          MLX_KEY_S
# define KEY_MOVE_LEFT              MLX_KEY_A
# define KEY_MOVE_RIGHT             MLX_KEY_D
# define KEY_ROTATE_LEFT            MLX_KEY_LEFT
# define KEY_ROTATE_RIGHT           MLX_KEY_RIGHT
# define KEY_RUN                    MLX_KEY_LEFT_SHIFT
# define KEY_INTERACT               MLX_KEY_E
# define KEY_MM_TOGGLE              MLX_KEY_M
# define KEY_FPS_TOGGLE             MLX_KEY_F

/* ========================================================================== */
/*                                PLAYER                                      */
/* ========================================================================== */
# define PLAYER_WALK_SPEED          0.05f
# define PLAYER_RUN_SPEED           0.09f
# define PLAYER_ROT_SPEED           0.07f

/* ========================================================================== */
/*                                TEXTURES                                    */
/* ========================================================================== */
# define TEX_NORTH                  0
# define TEX_SOUTH                  1
# define TEX_WEST                   2
# define TEX_EAST                   3
# define TEX_DOOR                   4
# define TEX_SPRITE_0               5
# define TEX_SPRITE_1               6
# define TEX_SPRITE_2               7
# define TEX_COUNT                  8

# define TEX_PATH_DOOR              "textures/door.png"
# define TEX_PATH_SPRITE_0          "textures/sprite1.png"
# define TEX_PATH_SPRITE_1          "textures/sprite2.png"
# define TEX_PATH_SPRITE_2          "textures/sprite3.png"

/* ========================================================================== */
/*                                MAP                                         */
/* ========================================================================== */
# define TILE_WALL                  '1'
# define TILE_DOOR                  'D'
# define TILE_SPRITE                'X'
# define TILE_FLOOR                 '0'

# define MAP_MAX_SPRITES            100
# define MAP_MAX_DOORS              50

# define MAP_DIM_HEIGHT             0
# define MAP_DIM_WIDTH              1

/* ========================================================================== */
/*                                SPRITES                                     */
/* ========================================================================== */
# define SPRITE_DEFAULT_SCALE       1.0f
# define SPRITE_DEFAULT_COLOR       0xFFFFFFFF
# define SPRITE_DEFAULT_TEXTURE     TEX_SPRITE_0
# define SPRITE_DEFAULT_SPEED       1.5f
# define SPRITE_DEFAULT_CHASING     0

# define SPRITE_START_COORD         -1
# define SPRITE_START_DIST          0.0f
# define SPRITE_START_PERP_DIST     0.0f
# define SPRITE_START_FRAME_INDEX   0
# define SPRITE_START_ANIM_TIMER    0.0f

# define SPRITE_ANIM_INTERVAL       0.2f
# define SPRITE_FRAME_DT            0.016f
# define SPRITE_STOP_DIST           0.5f
# define SPRITE_LOS_STEP            0.1f
# define SPRITE_COLLISION_MARGIN    0.4f

/* ========================================================================== */
/*                                DOORS                                       */
/* ========================================================================== */
# define DOOR_OPEN_RATIO_FULL       1.0f
# define DOOR_OPEN_RATIO_START      0.0f
# define DOOR_OPEN_SPEED            0.05f
# define DOOR_TOGGLE_RANGE          0.8f
# define DOOR_PASSABLE_RATIO        0.5f

/* ========================================================================== */
/*                                RAYCASTING                                  */
/* ========================================================================== */
# define MAX_DDA_STEPS              1000
# define AXIS_X                     0
# define AXIS_Y                     1
# define RAY_MAX_DIST               1e30f
# define RAY_MIN_PERP_DIST          0.001f
# define RAY_HALF_TILE_OFFSET       0.5f
# define RAY_HIT_NONE               0
# define RAY_HIT_WALL               1
# define RAY_HIT_DOOR               2
# define RAY_DELTA_DIST_INF         INFINITY
# define CAMERA_PLANE_SCALE         2.0f
# define CAMERA_PLANE_OFFSET        1.0f
# define SAFE_INV_DET_EPS           1e-8f

/* ========================================================================== */
/*                                DIRECTIONS                                  */
/* ========================================================================== */
# define DIR_COUNT                  4
# define DIR_NORTH_CHAR             'N'
# define DIR_SOUTH_CHAR             'S'
# define DIR_EAST_CHAR              'E'
# define DIR_WEST_CHAR              'W'

# define DIR_NORTH_X                0
# define DIR_NORTH_Y               -1
# define DIR_NORTH_PLANE_X          0.66f
# define DIR_NORTH_PLANE_Y          0
# define DIR_SOUTH_X                0
# define DIR_SOUTH_Y                1
# define DIR_SOUTH_PLANE_X         -0.66f
# define DIR_SOUTH_PLANE_Y          0
# define DIR_EAST_X                 1
# define DIR_EAST_Y                 0
# define DIR_EAST_PLANE_X           0
# define DIR_EAST_PLANE_Y           0.66f
# define DIR_WEST_X                -1
# define DIR_WEST_Y                 0
# define DIR_WEST_PLANE_X           0
# define DIR_WEST_PLANE_Y          -0.66f

/* ========================================================================== */
/*                                DIFFICULTY / AI                             */
/* ========================================================================== */
# define SPRITE_CHASE_SPEED_MULT     1.0f
# define SPRITE_VIEW_DISTANCE        5.0f

/* ========================================================================== */
/*                                GRAPHICS / VISUAL QUALITY                   */
/* ========================================================================== */
# define GRAPHICS_TEXTURE_QUALITY    1
# define GRAPHICS_SHOW_SHADOWS       1

/* ========================================================================== */
/*                                CAMERA / VIEW                               */
/* ========================================================================== */
# define CAMERA_FOV                 66.0f
# define CAMERA_HEIGHT               0.5f

/* ========================================================================== */
/*                                MISC / DEBUG                                */
/* ========================================================================== */
# define DEBUG_MODE                  0
# define FRAME_LIMIT                 60

#endif
