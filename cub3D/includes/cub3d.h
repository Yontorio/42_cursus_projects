/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:42:59 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/12 12:46:21 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "librairies.h"
# include "memtrack.h"
# include "mlx.h"
# include "stdfcts.h"
# include "utils.h"

# define INITIAL_CAPACITY 64

# define FRAME_CAP 120

# define MOVE_SPEED 0.03
# define ROT_SPEED 0.015

# define SPRITE_FRAME_COUNT 1

typedef struct s_sprite_params
{
	double			inv;
	double			tx;
	double			ty;
	int				ssx;
	int				sh;
	int				sw;
	int				bob;
	int				dsy;
	int				dey;
	int				dsx;
	int				dex;
}					t_sprite_params;

typedef struct s_mm
{
	int				sx;
	int				sy;
	int				cx;
	int				cy;
	int				radius;
}					t_mm;

# define WIDTH 1280
# define HEIGHT 720

# define MM_RADIUS 100
# define MM_TILE 9
# define MM_PADDING 19
# define FOV_ANGLE 0.577
# define MM_BR_THICK 4
# define MM_BR_COLOR 0x63120D
# define MM_BG_COLOR 0x000000
# define MM_TEXT_COLOR 0xFFFFFF

# define MM_PLAYER_RADIUS 4
# define MM_PLAYER_COLOR 0xAD0900
# define MOUSE_SENSOR 0.005

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}					t_keys;

typedef struct s_dda
{
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	double			side_x;
	double			side_y;
	int				step_x;
	int				step_y;
	int				side;
	char			tile;
}					t_dda;

typedef struct s_line
{
	int				height;
	int				start;
	int				end;
	double			dist;
}					t_line;

typedef struct s_cnt
{
	int				textures;
	int				colors;
	int				map;
}					t_cnt;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef struct s_tex_info
{
	t_img			*img;
	double			wall_x;
	int				x;
	int				y;
}					t_tex_info;

typedef struct s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef enum e_tex_id
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	DOOR
}					t_tex_id;

typedef struct s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
}					t_player;

typedef struct s_env
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor;
	int				ceiling;
}					t_env;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	t_player		player;
}					t_map;

typedef struct s_maze
{
	void			*mlx;
	void			*win;
	int				win_w;
	int				win_h;
	int				mouse_x;
	t_img			img;
	t_env			env;
	t_map			map;
	t_img			tex[6];
	struct s_sprite	*sprites;
	int				sprite_count;
	t_img			sprite_frames;
	int				sprite_frame_count;
	int				frame_tick;
	double			*zbuffer;
	t_keys			keys;
}					t_maze;

typedef struct s_sprite
{
	t_vec			pos;
	int				frame;
	double			dist;
	int				active;
}					t_sprite;

void				destroy_maze(void);
bool				config_parser(int ac, char **av);
bool				init_maze(t_maze **maze);
void				init_env(t_env *env);
void				init_img(t_img *img);
void				init_map(t_map *map);
bool				file_validity(int argc, char **argv);
void				extract_map(char **lines);
int					eternal_maze(void);
bool				maze_setup(void);
bool				error_exit(char *error_msg);
t_maze				**maze_struct(void);
int					render_frame(t_maze *maze);
void				render_minimap(t_maze *maze);
void				raycasting(t_maze *m);
void				put_pixel(t_img *img, int x, int y, int color);
void				load_textures(t_maze *m);
int					render_maze(t_maze *maze);
int					key_press(int key, t_maze *maze);
int					key_release(int key, t_maze *maze);
int					close_window(void);
int					mouse_rotate(int x, int y, t_maze *maze);
int					is_wall(t_maze *m, double y, double x);
void				move_forward(t_maze *m, t_player *p);
void				move_backward(t_maze *m, t_player *p);
void				move_left(t_maze *m, t_player *p);
void				move_right(t_maze *m, t_player *p);
void				rotate(t_player *p, double angle);
void				try_open_door(t_maze *m);
int					player_in_tile(t_player p, int tx, int ty);
void				parse_texture_line(char *line);
void				parse_color_line(char *line);
bool				is_map_line(char c);
void				parse_player(t_map *map);
void				check_map_chars(t_map *map);
void				check_map_closed(t_map *map);
int					is_valid_rgb(int n);
t_vec				v_add(t_vec a, t_vec b);
t_vec				v_scale(t_vec v, double s);
double				calc_distance(t_dda *d);
void				perform_dda(t_maze *m, t_dda *d);
void				init_ray(t_maze *m, int x, t_vec *ray);
void				init_dda(t_player *p, t_vec *ray, t_dda *d);
int					get_tex_pixel_safe(t_img *tex, int x, int y);
void				load_sprite_frames(t_maze *m);
void				init_sprites(t_maze *m);
void				sort_sprites(t_maze *m);
void				compute_all_distances(t_maze *m);
void				update_sprite_animation(t_maze *m);
void				render_sprites(t_maze *m);
void				render_single_sprite(t_maze *m, t_sprite *s);
void				collect_sprite(t_maze *m, t_player *p);
void				draw_player(t_img *img, t_mm mm);
void				draw_square_clipped(t_img *img, t_mm mm, int color);
void				draw_fov(t_player *p, t_img *img, t_mm mm);
void				pick_color(t_maze *maze, t_mm mm, char c);
void				for_each_circle_pixel(t_img *img, t_mm mm,
						void (*cb)(t_img *, t_mm, t_vec, int));
void				bg_pixel_cb(t_img *img, t_mm mm, t_vec axe, int dist_sq);
void				border_pixel_cb(t_img *img, t_mm mm, t_vec axe,
						int dist_sq);
int					square(int x);
void				put_pixel(t_img *img, int x, int y, int color);
int					get_pixel(t_img *img, int x, int y);
int					inside_circle(t_mm mm, int x, int y);
void				init_sprite_render_params(t_sprite *s, t_maze *m,
						t_sprite_params *p);
void				calculate_sprite_dimensions(t_sprite_params *p, t_maze *m);
void				clamp_sprite_bounds(t_sprite_params *p, t_maze *m);

#endif
