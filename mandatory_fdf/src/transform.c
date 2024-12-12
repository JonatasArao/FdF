/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:21 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/11 16:39:48 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_point(t_point *point, double scale)
{
	if (point)
	{
		point->p_x = point->x * scale;
		point->p_y = point->y * scale;
		point->p_z = point->z * scale;
	}
}

void	translate_point(t_point *point, int tx, int ty)
{
	if (point)
	{
		point->p_x += tx;
		point->p_y += ty;
	}
}

void	isometric_projection(t_point *point)
{
	double	rad_x;
	double	rad_z;
	int		p_x;
	int		p_y;
	int		p_z;

	rad_x = asin(tan(30 * M_PI / 180));
	rad_z = (270 * M_PI / 180) + (45 * M_PI / 180);
	if (point)
	{
		p_x = point->p_x;
		p_y = point->p_y;
		p_z = point->p_z;
		point->p_x = p_x * cos(rad_z) - p_y * sin(rad_z);
		point->p_y = p_x * sin(rad_z) + p_y * cos(rad_z);
		p_x = point->p_x;
		p_y = point->p_y;
		point->p_y = p_y * cos(rad_x) - p_z * sin(rad_x);
		point->p_z = p_y * sin(rad_x) + p_z * cos(rad_x);
	}
}

void	apply_transform(t_transform tr, t_list *points)
{
	t_point	*point;

	while (points)
	{
		point = (t_point *) points->content;
		scale_point(point, tr.scale);
		isometric_projection(point);
		translate_point(point, tr.translate_x, tr.translate_y);
		points = points->next;
	}
}
