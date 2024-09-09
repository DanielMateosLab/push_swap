/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:39:58 by damateos          #+#    #+#             */
/*   Updated: 2024/09/09 17:28:54 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_swap(t_stack *stack)
{
	if (stack->top < 1)
		return ;
	stack->stack[stack->top] ^= stack->stack[stack->top - 1];
	stack->stack[stack->top - 1] ^= stack->stack[stack->top];
	stack->stack[stack->top] ^= stack->stack[stack->top - 1];
}

void	stack_push(t_stack *stack1, t_stack *stack2)
{
	if (stack2->top < 0)
		return ;
	stack1->stack[++stack1->top] = stack2->stack[stack2->top--];
}

void	stack_rotate(t_stack *stack)
{
	(void) stack;
	return ;
}

void	stack_reverse_rotate(t_stack *stack)
{
	(void) stack;
	return ;
}
