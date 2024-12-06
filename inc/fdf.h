/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 07:26:15 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/06 18:42:14 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "mlx.h"
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 500
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 500
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
	int				x_2d;
	int				y_2d;
}	t_point;

typedef struct s_vector
{
	t_point	*a;
	t_point	*b;
}	t_vector;

typedef struct s_map
{
	t_list	*points;
	t_list	*vectors;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	canva;
	t_map	map;
}	t_fdf;

void	img_pix_put(t_img *img, int x, int y, int color);

int		parse_cell(char *cell, t_point *point);

t_list	*add_point(t_list **head, int x, int y, char *cell);

int		parse_line(int y, char *line_char, t_list **points);

void	parse_mapfile(int fd, t_list **points);

t_list	*extract_points(char *filename);

t_list	*add_vector(t_list **head, t_point *a, t_point *b);

t_list	*generate_vector_list(t_list *points);

void	isometric_projection(t_list *points);

void	bresenham_line_alg(t_img *img, t_point a, t_point b);

void	render_background(t_img *img, int color);

int		render(t_fdf *fdf);

#endif
