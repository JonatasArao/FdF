/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:40:44 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 09:58:44 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_cell(char *cell, t_point *point)
{
	char	*saveptr;
	char	*token;

	if (!cell || !point)
		return (0);
	token = ft_strtok_r(cell, ",", &saveptr);
	if (!token || (!ft_strall(token, ft_isdigit)
			&& !((*token == '+' || *token == '-')
				&& ft_strall(token + 1, ft_isdigit) && *(token + 1))))
		return (0);
	point->z = ft_atoi(token);
	token = ft_strtok_r(NULL, ",", &saveptr);
	if (token && *(token + 2) && !ft_strncmp(token, "0x", 2)
		&& ft_strall(token + 2, ft_isxdigit))
	{
		ft_strforeach(token + 2, ft_toupper);
		point->color = ft_atoi_base(token + 2, "0123456789ABCDEF");
		if (point->color > 0xFFFFFF)
			point->color = DEFAULT_COLOR;
	}
	else
		point->color = DEFAULT_COLOR;
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
	if (!parse_cell(cell, new_point))
	{
		ft_putendl_fd("Invalid value.", 2);
		return (ft_delpointer((void *) &new_point));
	}
	new_node = ft_lstnew(new_point);
	if (new_node == NULL)
	{
		ft_putendl_fd("New point allocation failed.", 2);
		return (ft_delpointer((void *) &new_point));
	}
	ft_lstadd_front(head, new_node);
	return (*head);
}

int	parse_line(int y, char *line_char, t_list **points)
{
	char	*saveptr;
	char	*cell;
	int		x;

	x = 0;
	cell = ft_strtok_r(line_char, " \n", &saveptr);
	while (cell != NULL)
	{
		if (!add_point(points, x, y, cell))
		{
			ft_lstclear(points, free);
			return (-1);
		}
		cell = ft_strtok_r(NULL, " \n", &saveptr);
		x++;
	}
	return (x);
}

void	parse_mapfile(int fd, t_list **points)
{
	char	*line_char;
	int		y;
	int		len;
	int		expected_len;

	y = 0;
	line_char = get_next_line(fd);
	while (line_char)
	{
		if (y == 0 || (len != -1 && len == expected_len))
		{
			len = parse_line(y, line_char, points);
			if (y == 0)
				expected_len = len;
			y++;
		}
		else if (*points)
		{
			ft_lstclear(points, free);
			if (len != expected_len)
				ft_putendl_fd("Found wrong line length.", 2);
		}
		free(line_char);
		line_char = get_next_line(fd);
	}
}

t_list	*extract_points(char *filename)
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
	parse_mapfile(fd, &points);
	if (!points)
		ft_putendl_fd("Invalid mapfile.", 2);
	if (close(fd) == -1)
	{
		perror("Error closing file");
		ft_lstclear(&points, free);
		return (NULL);
	}
	return (points);
}
