/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:01:47 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/25 10:24:53 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, t_point point)
{
	char	*pixel;

	if (point.x >= 0 && point.x < WINDOW_WIDTH
		&& point.y >= 0 && point.y < WINDOW_HEIGHT)
	{
		pixel = img->addr + (point.y * img->line_len
				+ point.x * (img->bits_per_pixel / 8));
		*(int *)pixel = point.color;
	}
}

void	render_background(t_img *img, int color)
{
	t_point	point;

	point.color = color;
	point.y = 0;
	while (point.y < WINDOW_HEIGHT)
	{
		point.x = 0;
		while (point.x < WINDOW_WIDTH)
		{
			img_pix_put(img, point);
			point.x++;
		}
		point.y++;
	}
}

int	render(t_fdf *fdf)
{
	if (fdf->win == NULL)
		return (1);
	render_background(&fdf->img, 0xFF0000);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
