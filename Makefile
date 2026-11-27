NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

INCLUDES = -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)

COMMON_SRC = \
      src/parsing/parse_file.c \
      src/parsing/parse_elements.c \
      src/parsing/parse_texture.c \
      src/parsing/parse_color.c \
      src/parsing/parse_map.c \
      src/parsing/check_map.c \
      src/parsing/init_player.c \
      src/utils/error.c \
      src/utils/free.c \
      src/utils/color.c \
      src/utils/parse_utils.c \
      src/render/init_mlx.c \
      src/render/img.c \
      src/render/ray.c \
      src/render/dda.c \
      src/render/wall.c \
      src/render/texture.c \
      src/input/movement.c \
      src/input/hooks.c
SRC = $(COMMON_SRC) \
      src/main.c
SRC_BONUS =$(COMMON_SRC) \
            src/main_bonus.c \
            src/input/hooks_bonus.c

ifeq ($(MODE),bonus)
BUILD_SRC = $(SRC_BONUS)
BUILD_MODE = bonus
else
BUILD_SRC = $(SRC)
BUILD_MODE = normal
endif

OBJ = $(BUILD_SRC:.c=.o)
MODE_STAMP = .cub3d-mode-$(BUILD_MODE)

all: $(NAME)

$(NAME): $(MODE_STAMP) $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(MODE_STAMP):
	rm -f .cub3d-mode-normal .cub3d-mode-bonus
	touch $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus:
	$(MAKE) MODE=bonus all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(SRC:.c=.o) $(SRC_BONUS:.c=.o)
	rm -f .cub3d-mode-normal .cub3d-mode-bonus

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re