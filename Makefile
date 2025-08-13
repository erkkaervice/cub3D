# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/04 15:36:34 by eala-lah          #+#    #+#              #
#    Updated: 2025/08/13 15:21:05 by eala-lah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
INCS		= -I ./incs/ -I ./libft/inc/ -I ./mlx/include/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= mlx/
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS	= -L $(MLX_DIR)/build -lmlx42 -lglfw -lm -ldl -pthread

SRC_DIR		= srcs/
SRC		= \
	cfg.c \
	cleanup.c \
	door.c \
	door_utils.c \
	fps.c \
	fps_utils.c \
	init_data.c \
	init_game.c \
	keys.c \
	main.c \
	map.c \
	map_utils.c \
	minimap.c \
	mouse.c \
	movement.c \
	raycast.c \
	render.c \
	sprites.c \
	sprites_utils.c \
	textures.c

OBJ_DIR		= obj/
OBJ_SUBDIR	= $(OBJ_DIR)cub3d/
OBJS		= $(addprefix $(OBJ_SUBDIR), $(SRC:.c=.o))

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror $(INCS) -g
GIT_FLAGS	= git clone --depth 1

all: $(LIBFT) $(MLX_LIB) $(OBJ_SUBDIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 2> /dev/null || { echo "Failed to create object directory." >&2; exit 1; }

$(OBJ_SUBDIR): | $(OBJ_DIR)
	@mkdir -p $(OBJ_SUBDIR) 2> /dev/null || { echo "Failed to create object subdirectory." >&2; exit 1; }

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/erkkaervice/libft.git $(LIBFT_DIR) > /dev/null 2>&1 || { echo "Failed to clone libft repository." >&2; exit 1; }; \
	fi
	@make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC -I ./inc/" > /dev/null 2>&1 || { echo "Failed to build libft library." >&2; exit 1; }
	@rm -f $(LIBFT_DIR)/README.md > /dev/null 2>&1 || { echo "Failed to remove README.md." >&2; exit 1; }

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		$(GIT_FLAGS) https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to clone MLX42." >&2; exit 1; }; \
	fi
	@cmake -B $(MLX_DIR)/build -S $(MLX_DIR) > /dev/null 2>&1 || { echo "Failed to configure MLX42 with CMake." >&2; exit 1; }
	@cmake --build $(MLX_DIR)/build > /dev/null 2>&1 || { echo "Failed to build MLX42." >&2; exit 1; }

$(OBJ_SUBDIR)%.o: $(SRC_DIR)%.c incs/cub3d.h
	@$(CC) $(CFLAGS) -c $< -o $@ 2> /dev/stderr || { echo "Failed to compile $<." >&2; exit 1; }

$(NAME): $(OBJS) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L $(LIBFT_DIR) -lft -o $(NAME) 2> /dev/stderr || { echo "Failed to create executable $(NAME)." >&2; exit 1; }

clean:
	@rm -rf $(OBJ_DIR) 2> /dev/null || { echo "Failed to clean object files." >&2; exit 1; }
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1 || { if [ -d "$(LIBFT_DIR)" ]; then echo "Failed to clean libft." >&2; exit 1; fi; }
	@rm -rf $(MLX_DIR)/build 2> /dev/null || true

fclean: clean
	@rm -f $(LIBFT) $(NAME) 2> /dev/stderr || { echo "Failed to remove generated files." >&2; exit 1; }
	@rm -rf $(LIBFT_DIR) 2> /dev/stderr || { \
		if [ -d "$(LIBFT_DIR)" ]; then \
			echo "Failed to remove libft directory." >&2; exit 1; \
		fi; \
	}
	@rm -rf $(MLX_DIR) 2> /dev/stderr || { \
		if [ -d "$(MLX_DIR)" ]; then \
			echo "Failed to remove mlx directory." >&2; exit 1; \
		fi; \
	}

re: fclean all

.PHONY: all clean fclean re
