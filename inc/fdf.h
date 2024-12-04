/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 07:26:15 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 11:13:34 by jarao-de         ###   ########.fr       */
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
# ifndef KEYPRESS
#  define KEYPRESS 2
# endif
# ifndef KEYPRESS_MASK
#  define KEYPRESS_MASK 1L
# endif
# ifndef CLOSE_BUTTON
#  define CLOSE_BUTTON 17
# endif
# ifndef ESC_KEY
#  define ESC_KEY 65307
# endif

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
}	t_point;

typedef struct s_vector
{
	t_point	*a;
	t_point	*b;
	int		delta_x;
	int		delta_y;
	int		direction_x;
	int		direction_y;
}	t_vector;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_list	*points;
}	t_fdf;

void	img_pix_put(t_img *img, t_point point);

int		parse_cell(char *cell, t_point *point);

t_list	*add_point(t_list **head, int x, int y, char *cell);

int		parse_line(int y, char *line_char, t_list **points);

void	parse_mapfile(int fd, t_list **points);

t_list	*extract_points(char *filename);

t_list	*add_vector(t_list **head, t_point *a, t_point *b);

void	render_background(t_img *img, int color);

int		render(t_fdf *fdf);

#endif
