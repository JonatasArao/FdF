/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:01:47 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 08:25:11 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, t_point point)
{
	char	*pixel;
	int		i;

	i = img->bits_per_pixel;
	pixel = img->addr + (point.y * img->line_len
			+ point.x * (img->bits_per_pixel / 8));
	while (i > 0)
	{
		i -= 8;
		if (img->endian != 0)
			*pixel++ = (point.color >> i) & 0xFF;
		else
			*pixel++ = (point.color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
	}
}

int	render(t_fdf *fdf)
{
	if (fdf->win == NULL)
		return (1);
	render_background(&fdf->img, 0xFFFFFF);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
