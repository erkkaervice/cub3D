NAME		= cub3D
INCS		= -I ./incs/ -I ./libft/inc/ -I ./mlx/include/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= mlx/
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS	= -L $(MLX_DIR)/build -lmlx42 -lglfw -lm -ldl -pthread

SRC_DIR		= srcs
SRC		= \
	core/main.c \
	core/init_data.c \
	core/init_entities.c \
	core/init_game.c \
	core/cleanup.c \
	\
	parsing/map.c \
	parsing/parsing.c \
	parsing/parsing2.c \
	parsing/parsing3.c \
	parsing/parsing4.c \
	parsing/parsing_utils.c \
	parsing/parsing_utils2.c \
	\
	graphics/blit.c \
	graphics/render.c \
	graphics/raycast.c \
	graphics/textures.c \
	\
	gameplay/input.c \
	gameplay/movement.c \
	gameplay/door.c \
	gameplay/door_utils.c \
	\
	hud/minimap.c \
	hud/fps.c \
	hud/fps_utils.c \
	\
	sprites/sprites_parsing.c \
	sprites/sprites_logic.c \
	sprites/sprites_behavior.c \

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror $(INCS) -g
GIT_FLAGS	= git clone --depth 1

all: $(LIBFT) $(MLX_LIB) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 2> /dev/null || { echo "Failed to create object directory." >&2; exit 1; }

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c incs/cub3d.h | $(OBJ_DIR)
	@mkdir -p $(dir $@)
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
