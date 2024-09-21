/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:01:16 by damateos          #+#    #+#             */
/*   Updated: 2024/09/21 14:19:55 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	stack_index(t_stack *stack, size_t index, t_direction direction)
{
	if (direction == PREV)
		index = (index + stack->taken - 1) % stack->taken;
	else
		index = (index + 1) % stack->taken;
	return (index);
}

size_t	stack_index_n(t_stack *stack, size_t index,
		t_direction direction, size_t n)
{
	if (direction == PREV)
		index = (index + stack->taken - n) % stack->taken;
	else
		index = (index + n) % stack->taken;
	return (index);
}

void	stack_print(t_stack *s)
{
	size_t	i;

	i = s->top;
	ft_printf("-----\ntop: %d\nbase: %d\ntaken: %d\ncapacity: %d\n-----\n",
		(int)i, (int)s->base, (int)s->taken, (int)s->capacity);
	while (i != s->base)
	{
		ft_printf("%d\n", s->stack[i]);
		if (i == 0)
		{
			i = s->taken - 1;
			continue ;
		}
		else
			i--;
	}
	ft_printf("-----\n");
}

int	stack_is_sorted(t_stack *s)
{
	size_t	i;

	i = s->top;
	while (i != s->base)
	{
		if (s->stack[i] > s->stack[i - 1])
			break ;
		i--;
	}
	if (i == s->base)
		return (1);
	i = s->top;
	while (i != s->base)
	{
		if (s->stack[i] < s->stack[i - 1])
			return (0);
		i--;
	}
	return (1);
}
