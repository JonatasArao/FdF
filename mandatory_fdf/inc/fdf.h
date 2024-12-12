/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 07:26:15 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/12 14:49:08 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "libft.h"
# include "mlx.h"
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1024
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 768
# endif
# ifndef DEFAULT_COLOR
#  define DEFAULT_COLOR 0xFFFFFF
# endif
# ifndef ISO_ANGLE
#  define ISO_ANGLE 30
# endif
# define KEYPRESS 2
# define KEYPRESS_MASK 1L
# define CLOSE_BUTTON 17
# define ESC_KEY 65307

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	unsigned int	color;
	int				x;
	int				y;
	int				z;
	int				p_x;
	int				p_y;
	int				p_z;
}	t_point;

typedef struct s_vector
{
	t_point	*a;
	t_point	*b;
}	t_vector;

typedef struct s_transform
{
	double	scale;
	int		translate_x;
	int		translate_y;
}	t_transform;

typedef struct s_map
{
	t_list			*points;
	t_list			*vectors;
	t_transform		transform;
	int				width;
	int				height;
	int				max_x;
	int				max_y;
	int				min_x;
	int				min_y;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	canva;
	t_map	map;
}	t_fdf;

void	img_pix_put(t_img *img, int x, int y, int color);

t_list	*extract_points(char *filename);

t_list	*generate_vector_list(t_list *points);

void	scale_point(t_point *point, double scale);

void	isometric_projection(t_point *point);

void	translate_point(t_point *point, int tx, int ty);

void	apply_transform(t_transform proj, t_list *points);

int		init_map(t_map *map, char *mapfile);

void	bresenham_line_alg(t_img *img, t_point a, t_point b);

void	render_background(t_img *img, int color);

int		render(t_fdf *fdf);

#endif
