/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:39:58 by damateos          #+#    #+#             */
/*   Updated: 2024/09/20 21:04:19 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_swap(t_stack *stack)
{
	size_t	top_prev_index;

	if (stack->taken < 2)
		return ;
	top_prev_index = stack_index(stack, stack->top, PREV);
	stack->stack[stack->top] ^= stack->stack[top_prev_index];
	stack->stack[top_prev_index] ^= stack->stack[stack->top];
	stack->stack[stack->top] ^= stack->stack[top_prev_index];
}

void	stack_push(t_stack *stack1, t_stack *stack2)
{
	if (stack2->taken == 0 || stack1->taken == stack1->capacity)
		return ;
	stack1->top = stack_index(stack1, stack1->top, NEXT);
	stack1->stack[stack1->top] = stack2->stack[stack2->top];
	stack2->top = stack_index(stack2, stack2->top, PREV);
	stack1->taken++;
	stack2->taken--;
}

/* ROTATE example
 * 0123_ r b0 t3 0123
 * 0123_ r b1 t0 1230
 * 0123_ r b2 t1 2301
 * 0123_ r b3 t2 3012
 * ------------
 * When rotating, we update the top and base.
 * We use current_index % stack->taken to wrap around the stack.
 * to wrap around the stack.
 * 012 r b0 t3 012
 * 012 r b1 t4 120
 * -- REVERSE ROTATE --
 * 0123_ rr b0 t3 0123
 * 0123_ rr b3 t2 3012
 * 0123_ rr b2 t1 2301
 * 0123_ rr b1 t0 1230
 * When reverse rotating, we reduce the top and base,
 * and wrap around when they go below 0.
 */
void	stack_rotate(t_stack *stack)
{
	stack->top = stack_index(stack, stack->top, NEXT);
	stack->base = stack_index(stack, stack->base, NEXT);
}

void	stack_reverse_rotate(t_stack *stack)
{
	stack->top = stack_index(stack, stack->top, PREV);
	stack->base = stack_index(stack, stack->base, PREV);
}
