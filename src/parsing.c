/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:40:44 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/03 11:34:51 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_cell_data(char *cell, t_point *point)
{
	char	*saveptr;
	char	*number;
	char	*color;

	if (!cell || !point)
		return (0);
	number = ft_strtok_r(cell, ",", &saveptr);
	if (!ft_strall(number, ft_isdigit) && !((*number == '+' || *number == '-')
			&& ft_strall(number + 1, ft_isdigit)))
		return (0);
	color = ft_strtok_r(NULL, ",", &saveptr);
	if (!color)
		point->color = DEFAULT_COLOR;
	else if (*(color + 2) && !ft_strncmp(color, "0x", 2)
		&& ft_strall(color + 2, ft_isxdigit))
	{
		ft_strforeach(color + 2, ft_toupper);
		point->color = ft_atoi_base(color + 2, "0123456789ABCDEF");
	}
	else
		return (0);
	point->z = ft_atoi(number);
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
	ft_lstadd_front(head, new_node);
	return (*head);
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
