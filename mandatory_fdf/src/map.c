/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:06:47 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/12 14:45:36 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_bounds(t_map *map, t_list *points)
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
		if (point.p_x < map->min_x)
			map->min_x = point.p_x;
		if (point.p_y < map->min_y)
			map->min_y = point.p_y;
		if (point.p_x > map->max_x)
			map->max_x = point.p_x;
		if (point.p_y > map->max_y)
			map->max_y = point.p_y;
		points = points->next;
	}
	map->width = map->max_x - map->min_x;
	map->height = map->max_y - map->min_y;
}

static void	initial_position(t_map *map)
{
	double	scale_x;
	double	scale_y;
	double	max_scale;

	scale_x = (double)(WINDOW_WIDTH * 0.85) / map->width;
	scale_y = (double)(WINDOW_HEIGHT * 0.85) / map->height;
	max_scale = fmin(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.1);
	map->transform.scale = fmin(scale_x, scale_y);
	if (scale_x > WINDOW_WIDTH * 0.05 || scale_y > WINDOW_HEIGHT * 0.05)
		map->transform.scale *= 0.75;
	map->transform.scale = fmin(map->transform.scale, max_scale);
	map->transform.translate_x = (WINDOW_WIDTH - map->width
			* map->transform.scale) / 2
		- map->min_x * map->transform.scale;
	map->transform.translate_y = (WINDOW_HEIGHT - map->height
			* map->transform.scale) / 2
		- map->min_y * map->transform.scale;
}

int	init_map(t_map *map, char *mapfile)
{
	map->points = extract_points(mapfile);
	map->vectors = generate_vector_list(map->points);
	if (!map->vectors)
	{
		ft_putendl_fd("Can't generate vectors.", 2);
		ft_lstclear(&map->points, free);
	}
	if (!map->points)
		return (0);
	update_map_bounds(map, map->points);
	initial_position(map);
	apply_transform(map->transform, map->points);
	return (1);
}
