#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <fcntl.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// length of the camera plane: FOV = 2 * atan(0.66) = about 66 degrees
# define PLANE_LEN 0.66

// how far the player moves / turns (in radians) each frame
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04
// how close the player can get to a wall
# define WALL_MARGIN 0.2

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

// 1 while the key is held down, 0 when released
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

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
	t_keys		keys;
}	t_game;

/*        PARSING        */
void	parse_file(t_game *game, char *path);
int		parse_elements(t_game *game);
void	parse_map(t_game *game, int start);
void	check_map(t_game *game);
void	init_player(t_game *game);
void	parse_texture(t_game *game, char **dst, char *value);
void	parse_color(t_game *game, t_color *color, char *value);

/*        UTILS        */
void	error_exit(t_game *game, char *msg);
int		is_space(char c);
char	*skip_spaces(char *str);
void	free_grid(char **grid);
void	clean_exit(t_game *game, int status);

/*        INPUT        */
void	init_hooks(t_game *game);
void	update_player(t_game *game);

/*        RENDER        */
void	init_mlx(t_game *game);

#endif
