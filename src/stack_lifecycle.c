/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:44:20 by damateos          #+#    #+#             */
/*   Updated: 2024/08/24 11:52:13 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_init(t_stack *stack, int size)
{
	stack->stack = (int *)malloc(sizeof(int) * size);
	stack->top = -1;
	stack->capacity = size;
	stack->base = 0;
}

void	stack_destroy(t_stack *stack)
{
	ft_free((void **)&stack->stack);
	stack->top = -1;
}
