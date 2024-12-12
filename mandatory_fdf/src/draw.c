/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:45:07 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/12 14:45:10 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	color_line_gradient(int a_color, int b_color, int len, int diff)
{
	double	ratio_rgb[3];
	int		a_rgb[3];
	int		b_rgb[3];
	int		gradient_rgb[3];
	int		gradient_color;

	a_rgb[0] = (a_color >> 16) & 0xFF;
	a_rgb[1] = (a_color >> 8) & 0xFF;
	a_rgb[2] = a_color & 0xFF;
	b_rgb[0] = (b_color >> 16) & 0xFF;
	b_rgb[1] = (b_color >> 8) & 0xFF;
	b_rgb[2] = b_color & 0xFF;
	ratio_rgb[0] = (double)(a_rgb[0] - b_rgb[0]) / (double)len;
	ratio_rgb[1] = (double)(a_rgb[1] - b_rgb[1]) / (double)len;
	ratio_rgb[2] = (double)(a_rgb[2] - b_rgb[2]) / (double)len;
	gradient_rgb[0] = b_rgb[0] + diff * ratio_rgb[0];
	gradient_rgb[1] = b_rgb[1] + diff * ratio_rgb[1];
	gradient_rgb[2] = b_rgb[2] + diff * ratio_rgb[2];
	gradient_color = (gradient_rgb[0] << 16)
		+ (gradient_rgb[1] << 8) + gradient_rgb[2];
	return (gradient_color);
}

static void	bresenham_line_alg_low_slope(t_img *img, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	direction;
	int	decision;

	delta_x = b.p_x - a.p_x;
	delta_y = b.p_y - a.p_y;
	direction = 1;
	if (delta_y < 0)
		direction = -1;
	delta_y *= direction;
	decision = 2 * delta_y - delta_x;
	while (a.p_x <= b.p_x)
	{
		img_pix_put(img, a.p_x, a.p_y,
			color_line_gradient(a.color, b.color, delta_x, b.p_x - a.p_x));
		a.p_x++;
		if (decision > 0)
		{
			a.p_y += direction;
			decision = decision + (2 * (delta_y - delta_x));
		}
		else
			decision = decision + 2 * delta_y;
	}
}

static void	bresenham_line_alg_high_slope(t_img *img, t_point a, t_point b)
{
	int	delta_x;
	int	delta_y;
	int	direction;
	int	decision;

	delta_x = b.p_x - a.p_x;
	delta_y = b.p_y - a.p_y;
	direction = 1;
	if (delta_x < 0)
		direction = -1;
	delta_x *= direction;
	decision = 2 * delta_x - delta_y;
	while (a.p_y <= b.p_y)
	{
		img_pix_put(img, a.p_x, a.p_y,
			color_line_gradient(a.color, b.color, delta_y, b.p_y - a.p_y));
		a.p_y++;
		if (decision > 0)
		{
			a.p_x += direction;
			decision = decision + (2 * (delta_x - delta_y));
		}
		else
			decision = decision + 2 * delta_x;
	}
}

void	bresenham_line_alg(t_img *img, t_point a, t_point b)
{
	if (abs(b.p_y - a.p_y) < abs(b.p_x - a.p_x))
	{
		if (a.p_x > b.p_x)
			bresenham_line_alg_low_slope(img, b, a);
		else
			bresenham_line_alg_low_slope(img, a, b);
	}
	else
	{
		if (a.p_y > b.p_y)
			bresenham_line_alg_high_slope(img, b, a);
		else
			bresenham_line_alg_high_slope(img, a, b);
	}
}
