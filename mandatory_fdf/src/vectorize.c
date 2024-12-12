/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:24:40 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/12 14:46:36 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*add_vector(t_list **head, t_point *a, t_point *b)
{
	t_vector	*new_vector;
	t_list		*new_node;

	new_vector = malloc(sizeof(t_vector));
	if (new_vector == NULL)
		return (NULL);
	new_vector->a = a;
	new_vector->b = b;
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
