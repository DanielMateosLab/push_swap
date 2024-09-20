/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:44:20 by damateos          #+#    #+#             */
/*   Updated: 2024/09/20 20:11:39 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/** Initializes the stack with the given numbers. The first number
 * is the top of the stack.
 */
void	stack_init_from_nums(t_stack *stack, char **numbers)
{
	size_t	size;
	size_t	i;

	size = str_array_len(numbers);
	stack->stack = (int *)malloc(sizeof(int) * size);
	stack->capacity = size;
	stack->top = size - 1;
	stack->base = 0;
	stack->taken = size;
	i = 0;
	while (i < size)
	{
		stack->stack[i] = ft_atoi(numbers[size - i - 1]);
		i++;
	}
}

void	stack_init_empty(t_stack *stack, int size)
{
	stack->stack = (int *)malloc(sizeof(int) * size);
	stack->top = 0;
	stack->capacity = size;
	stack->taken = 0;
	stack->base = 0;
}


void	stack_destroy(t_stack *stack)
{
	ft_free((void **)&stack->stack);
	stack->top = -1;
	stack->base = 0;
	stack->taken = 0;
	stack->capacity = 0;
}
