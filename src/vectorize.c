/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:24:40 by jarao-de          #+#    #+#             */
/*   Updated: 2024/12/04 11:35:19 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*add_vector(t_list **head, t_point *a, t_point *b)
{
	t_vector	*new_vector;
	t_list		*new_node;

	new_vector = malloc(sizeof(t_vector));
	if (new_vector == NULL)
		return (NULL);
	new_vector->a = a;
	new_vector->b = b;
	new_vector->delta_x = b->x - a->x;
	new_vector->delta_y = b->y - a->y;
	new_vector->direction_x = 1;
	if (new_vector->delta_x < 0)
		new_vector->direction_x = -1;
	new_vector->direction_y = 1;
	if (new_vector->delta_y < 0)
		new_vector->direction_y = -1;
	new_node = ft_lstnew(new_vector);
	if (new_node == NULL)
	{
		ft_putendl_fd("New vector allocation failed.", 2);
		return (ft_delpointer((void *) &new_vector));
	}
	ft_lstadd_front(head, new_node);
	return (*head);
}
