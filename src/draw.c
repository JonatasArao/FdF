/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:45:07 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/06 17:46:25 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham_line_alg_low_slope(t_img *img, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	direction;
	int	decision;

	delta_x = b.x_2d - a.x_2d;
	delta_y = b.y_2d - a.y_2d;
	direction = 1;
	if (delta_y < 0)
		direction = -1;
	delta_y *= direction;
	decision = 2 * delta_y - delta_x;
	while (a.x_2d <= b.x_2d)
	{
		img_pix_put(img, a.x_2d, a.y_2d, a.color);
		a.x_2d++;
		if (decision > 0)
		{
			a.y_2d += direction;
			decision = decision + (2 * (delta_y - delta_x));
		}
		else
			decision = decision + 2 * delta_y;
	}
}

void	bresenham_line_alg_high_slope(t_img *img, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	direction;
	int	decision;

	delta_x = b.x_2d - a.x_2d;
	delta_y = b.y_2d - a.y_2d;
	direction = 1;
	if (delta_x < 0)
		direction = -1;
	delta_x *= direction;
	decision = 2 * delta_x - delta_y;
	while (a.y_2d <= b.y_2d)
	{
		img_pix_put(img, a.x_2d, a.y_2d, a.color);
		a.y_2d++;
		if (decision > 0)
		{
			a.x_2d += direction;
			decision = decision + (2 * (delta_x - delta_y));
		}
		else
			decision = decision + 2 * delta_x;
	}
}

void	bresenham_line_alg(t_img *img, t_point a, t_point b)
{
	if (abs(b.y_2d - a.y_2d) < abs(b.x_2d - a.x_2d))
	{
		if (a.x_2d > b.x_2d)
			bresenham_line_alg_low_slope(img, b, a);
		else
			bresenham_line_alg_low_slope(img, a, b);
	}
	else
	{
		if (a.y_2d > b.y_2d)
			bresenham_line_alg_high_slope(img, b, a);
		else
			bresenham_line_alg_high_slope(img, a, b);
	}
}
