NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

INCLUDES = -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC = src/main.c \
      src/parsing/parse_file.c \
      src/parsing/parse_elements.c \
      src/parsing/parse_texture.c \
      src/parsing/parse_color.c \
      src/parsing/parse_map.c \
      src/parsing/check_map.c \
      src/utils/error.c \
      src/utils/free.c \
      src/utils/color.c \
      src/utils/parse_utils.c \
      src/input/hooks.c \
      src/render/init_mlx.c \
      src/render/img.c \
      src/render/player.c \
      
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
