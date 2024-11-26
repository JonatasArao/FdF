/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:40:44 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/26 18:11:56 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_cell_data(char *cell, t_point *point)
{
	int	num_i;
	int	color_i;

	num_i = 0;
	if (!cell || !point || !ft_isdigit(cell[num_i++]))
		return (0);
	while (ft_isdigit(cell[num_i]))
		num_i++;
	if (cell[num_i] == ',' && ft_strncmp(&cell[num_i], ",0x", 3) == 0)
	{
		color_i = num_i + 3;
		while (cell[color_i])
		{
			cell[color_i] = ft_toupper(cell[color_i]);
			color_i++;
		}
		if (!ft_isxdigit(cell[color_i - 1]))
			return (0);
		point->color = ft_atoi_base(&cell[num_i + 3], "0123456789ABCDEF");
	}
	else if (cell[num_i] != '\0')
		return (0);
	if (cell[num_i] == '\0' || cell[num_i] == ',')
		point->z = ft_atoi(cell);
	return (1);
}

t_list	*parse_mapfile(char *filename)
{
	t_list	*points;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot open file");
		return (NULL);
	}
	points = NULL;
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (NULL);
	}
	return (points);
}
