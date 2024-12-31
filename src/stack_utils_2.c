/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:55:07 by damateos          #+#    #+#             */
/*   Updated: 2024/12/31 12:48:36 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Converts a stack to an array of integers.
 * @remark Order 1 means the top is the smallest
 */
int	*stack_to_array(t_stack *stack, int order)
{
	int			*array;
	t_bi_list	*i;
	size_t		j;

	array = (int *)malloc(stack->size * sizeof(int));
	if (!array)
		return (NULL);
	if (order == 1)
		i = stack->top;
	else
		i = stack->base;
	j = 0;
	while (i)
	{
		array[j] = i->content;
		if (order == 1)
			i = i->prev;
		else
			i = i->next;
		j++;
	}
	return (array);
}
