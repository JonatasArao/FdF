/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:07:21 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/06 18:39:14 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_list *points)
{
	t_point	*point;

	while (points)
	{
		point = (t_point *) points->content;
		if (point)
		{
			point->x_2d = (point->x - point->y)
				* cos(ISO_ANGLE * M_PI / 180);
			point->y_2d = (point->x + point->y)
				* sin(ISO_ANGLE * M_PI / 180) - point->z;
		}
		points = points->next;
	}
}
