/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:40:44 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/27 11:57:51 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_cell_data(char *cell, t_point *point)
{
	int	num_i;
	int	color_i;

	num_i = 0;
	if (!cell || !point || ((cell[num_i] == '-' || cell[num_i] == '+')
			&& ft_isdigit(cell[num_i++])))
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
	point->z = ft_atoi(cell);
	return (1);
}

t_list	*add_point(t_list **head, int x, int y, char *cell)
{
	t_point	*new_point;
	t_list	*new_node;

	new_point = malloc(sizeof(t_point));
	if (new_point == NULL)
		return (NULL);
	new_point->x = x;
	new_point->y = y;
	if (!parse_cell_data(cell, new_point))
		return (ft_delpointer((void *) &new_point));
	new_node = ft_lstnew(new_point);
	if (new_node == NULL)
		return (ft_delpointer((void *) &new_point));
	ft_lstadd_back(head, new_node);
	return (*head);
}

void	get_mapfile_data(int fd, t_list **points)
{
	char	*line_char;
	char	**line;
	int		x;
	int		y;

	x = 0;
	line_char = get_next_line(fd);
	while (line_char)
	{
		x++;
		y = 0;
		line = ft_split(ft_strtrim(line_char, " \n"), ' ');
		free(line_char);
		while (line[y] != NULL)
		{
			add_point(points, x, y, line[y]);
			y++;
		}
		ft_free_matrix((void **)line, y);
		line_char = get_next_line(fd);
	}
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
	get_mapfile_data(fd, &points);
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (NULL);
	}
	return (points);
}
