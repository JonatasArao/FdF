/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:06:47 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/08 18:34:22 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_map_bounds(t_map *map, t_list *points)
{
	t_point	point;

	if (!points)
		return ;
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	while (points)
	{
		point = *(t_point *)points->content;
		isometric_projection(&point);
		if (point.x_2d < map->min_x)
			map->min_x = point.x_2d;
		if (point.y_2d < map->min_y)
			map->min_y = point.y_2d;
		if (point.x_2d > map->max_x)
			map->max_x = point.x_2d;
		if (point.y_2d > map->max_y)
			map->max_y = point.y_2d;
		points = points->next;
	}
	map->width = map->max_x - map->min_x;
	map->height = map->max_y - map->min_y;
}

void	initial_projection(t_map *map)
{
	double	scale_x;
	double	scale_y;
	double	scale;

	scale_x = (double)(WINDOW_WIDTH * 0.8) / map->width;
	scale_y = (double)(WINDOW_HEIGHT * 0.8) / map->height;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	if (scale > WINDOW_WIDTH * 0.05 || scale > WINDOW_HEIGHT * 0.05)
		scale *= 0.6;
	map->projection.scale = scale;
	map->projection.translate_x = (WINDOW_WIDTH - map->width * scale) / 2
		- map->min_x * scale;
	map->projection.translate_y = (WINDOW_HEIGHT - map->height * scale) / 2
		- map->min_y * scale;
}

int	init_map(t_map *map, char *mapfile)
{
	map->points = extract_points(mapfile);
	map->vectors = generate_vector_list(map->points);
	if (!map->vectors)
		ft_lstclear(&map->points, free);
	if (!map->points)
		return (0);
	update_map_bounds(map, map->points);
	initial_projection(map);
	apply_projection(map->projection, map->points);
	return (1);
}
