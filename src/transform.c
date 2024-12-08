/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:21 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/07 23:01:25 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_point(t_point *point, double scale)
{
	if (point)
	{
		point->x_2d = point->x * scale;
		point->y_2d = point->y * scale;
		point->z = point->z * scale;
	}
}

void	isometric_projection(t_point *point)
{
	double	rad;
	int		x_2d;
	int		y_2d;

	rad = ISO_ANGLE * M_PI / 180;
	if (point)
	{
		x_2d = point->x_2d;
		y_2d = point->y_2d;
		point->x_2d = (x_2d - y_2d) * cos(rad);
		point->y_2d = (x_2d + y_2d) * sin(rad) - point->z;
	}
}

void	translate_point(t_point *point, int tx, int ty)
{
	if (point)
	{
		point->x_2d += tx;
		point->y_2d += ty;
	}
}

void	apply_projection(t_projection proj, t_list *points)
{
	t_point	*point;

	while (points)
	{
		point = (t_point *) points->content;
		scale_point(point, proj.scale);
		isometric_projection(point);
		translate_point(point, proj.translate_x, proj.translate_y);
		points = points->next;
	}
}
