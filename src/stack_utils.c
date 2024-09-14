/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:01:16 by damateos          #+#    #+#             */
/*   Updated: 2024/09/14 23:08:11 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	stack_index(t_stack *stack, size_t index, t_direction direction)
{
	if (direction == PREV)
	{
		if (index == 0)
			index = stack->taken - 1;
		else
			index--;
	}
	else
		index = (index + 1) % stack->taken;
	return (index);
}
