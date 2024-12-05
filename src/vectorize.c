/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:24:40 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/05 17:28:10 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_vector_properties(void *vector_ptr)
{
	t_vector	*vector;

	if (vector_ptr)
	{
		vector = (t_vector *)vector_ptr;
		if (vector-> a && vector->b)
		{
			vector->delta_x = vector->b->x - vector->a->x;
			vector->delta_y = vector->b->y - vector->a->y;
			vector->direction_x = 1;
			if (vector->delta_x < 0)
				vector->direction_x = -1;
			vector->direction_y = 1;
			if (vector->delta_y < 0)
				vector->direction_y = -1;
		}
	}
}

t_list	*add_vector(t_list **head, t_point *a, t_point *b)
{
	t_vector	*new_vector;
	t_list		*new_node;

	new_vector = malloc(sizeof(t_vector));
	if (new_vector == NULL)
		return (NULL);
	new_vector->a = a;
	new_vector->b = b;
	set_vector_properties(new_vector);
	new_node = ft_lstnew(new_vector);
	if (new_node == NULL)
	{
		ft_putendl_fd("New vector allocation failed.", 2);
		ft_lstclear(head, free);
		return (ft_delpointer((void *) &new_vector));
	}
	ft_lstadd_front(head, new_node);
	return (*head);
}

t_list	*generate_vector_list(t_list *points)
{
	t_list	*next;
	t_list	*vectors;
	t_point	*a;
	t_point	*b;

	vectors = NULL;
	while (points)
	{
		a = (t_point *)points->content;
		next = points->next;
		while (next)
		{
			b = (t_point *)next->content;
			if ((a->y == b->y && a->x - 1 == b->x)
				|| (a->x == b->x && a->y - 1 == b-> y))
				if (!add_vector(&vectors, a, b))
					break ;
			if (a->x == b->x && a->y - 1 == b->y)
				break ;
			next = next->next;
		}
		points = points->next;
	}
	return (vectors);
}
