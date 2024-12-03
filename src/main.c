/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 07:34:38 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/03 16:00:46 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_display(fdf->mlx);
	ft_lstclear(&fdf->points, free);
	free(fdf->mlx);
	exit(0);
	return (0);
}

static int	handle_keypress(int keysym, t_fdf *fdf)
{
	if (keysym == ESC_KEY)
		close_window(fdf);
	return (0);
}

static int	init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"FdF - Mandatory");
	if (fdf->win == NULL)
	{
		free(fdf->mlx);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_putendl_fd("Usage : ./fdf_linux <filename>", 2);
		return (1);
	}
	fdf.points = extract_points(argv[1]);
	if (!fdf.points || !init_window(&fdf))
		return (1);
	fdf.img.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel,
			&fdf.img.line_len, &fdf.img.endian);
	mlx_loop_hook(fdf.mlx, &render, &fdf);
	mlx_hook(fdf.win, CLOSE_BUTTON, 0, close_window, &fdf);
	mlx_hook(fdf.win, KEYPRESS, KEYPRESS_MASK, &handle_keypress, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
