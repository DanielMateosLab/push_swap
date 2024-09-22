/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:39:58 by damateos          #+#    #+#             */
/*   Updated: 2024/09/22 16:41:55 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_swap(t_stack *stack)
{
	t_bi_list	*first;
	t_bi_list	*second;
	t_bi_list	*third;

	if (stack->size < 2)
		return ;
	first = stack->top->prev;
	second = stack->top;
	third = first->prev;
	if (third)
	{
		third->next = second;
		second->prev = third;
	}
	else
	{
		second->prev = NULL;
		stack->base = second;
	}
	second->next = first;
	first->prev = second;
	first->next = NULL;
	stack->top = first;
}

void	stack_push(t_stack *stack1, t_stack *stack2)
{
	t_bi_list	*stack1_new_top;

	if (stack2->size == 0)
		return ;
	stack1->size++;
	stack2->size--;
	stack1_new_top = stack2->top;
	if (!stack2->size)
	{
		stack2->base = NULL;
		stack2->top = NULL;
	}
	else
	{
		stack2->top->prev->next = NULL;
		stack2->top = stack2->top->prev;
	}
	if (stack1->size == 1)
	{
		stack1->base = stack1_new_top;
		stack1->top = stack1_new_top;
		stack1_new_top->prev = NULL;
		stack1_new_top->next = NULL;
	}
	else
	{
		stack1->top->next = stack1_new_top;
		stack1_new_top->prev = stack1->top;
		stack1->top = stack1_new_top;
	}
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
	t_bi_list	*new_base;

	new_base = stack->top;
	stack->top = stack->top->prev;
	stack->top->next = NULL;
	new_base->next = stack->base;
	new_base->prev = NULL;
	stack->base->prev = new_base;
	stack->base = new_base;
}

void	stack_reverse_rotate(t_stack *stack)
{
	t_bi_list	*new_top;

	new_top = stack->base;
	stack->base = stack->base->next;
	stack->base->prev = NULL;
	new_top->next = NULL;
	new_top->prev = stack->top;
	stack->top->next = new_top;
	stack->top = new_top;
}
