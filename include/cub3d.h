#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>

# define KEY_ESC 65307

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* information parsed from .cub */
typedef struct s_config
{
	t_texture	textures;
	t_color		floor;
	t_color		ceiling;
}	t_config;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_image		image;
	char		**lines;
}	t_game;

/* parsing/parse_file.c */
void	parse_file(t_game *game, char *path);

/* parsing/parse_elements.c */
int		parse_elements(t_game *game);

/* parsing/parse_map.c */
void	parse_map(t_game *game, int start);

/* parsing/check_map.c */
void	check_map(t_game *game);

/* parsing/init_player.c */
void	init_player(t_game *game);

/* parsing/parse_texture.c */
void	parse_texture(t_game *game, char **dst, char *value);

/* parsing/parse_color.c */
void	parse_color(t_game *game, t_color *color, char *value);

/* utils/error.c */
void	error_exit(t_game *game, char *msg);

/* utils/parse_utils.c */
int		is_space(char c);
char	*skip_spaces(char *str);

/* utils/free.c */
void	free_grid(char **grid);
void	clean_exit(t_game *game, int status);

/* input/hooks.c */
void	init_hooks(t_game *game);

/* render/init_mlx.c */
void	init_mlx(t_game *game);

#endif
