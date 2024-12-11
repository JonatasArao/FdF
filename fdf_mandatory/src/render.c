/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:01:47 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/06 17:49:35 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= 0 && x < WINDOW_WIDTH
		&& y >= 0 && y < WINDOW_HEIGHT)
	{
		i = img->bits_per_pixel;
		pixel = img->addr + (y * img->line_len
				+ x * (img->bits_per_pixel / 8));
		while (i > 0)
		{
			i -= 8;
			if (img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bits_per_pixel - 8 - i))
					& 0xFF;
		}
	}
}

int	render(t_fdf *fdf)
{
	t_list		*vectors;
	t_vector	*current;

	if (fdf->win == NULL)
		return (1);
	vectors = fdf->map.vectors;
	while (vectors)
	{
		current = (t_vector *) vectors->content;
		bresenham_line_alg(&fdf->canva, *(current->a), *(current->b));
		vectors = vectors->next;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->canva.img, 0, 0);
	return (0);
}
