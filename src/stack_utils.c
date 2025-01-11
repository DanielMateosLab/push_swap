/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:01:16 by damateos          #+#    #+#             */
/*   Updated: 2025/01/11 22:37:29 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/** Returns a string representation of the stack.
 * Order 1 prints from base to top.
 * Order -1 prints from top to base. */
char	*stack_to_string(t_stack *stack, int order)
{
	char			*result;
	t_bi_list		*i;
	char			*num_str;

	result = ft_strdup("");
	if (order == -1)
		i = stack->top;
	else
		i = stack->base;
	while (i)
	{
		num_str = ft_itoa(i->content);
		ft_strjoin_mut(&result, num_str);
		free(num_str);
		if (order == -1)
			i = i->prev;
		else
			i = i->next;
		if (i)
			ft_strjoin_mut(&result, " ");
	}
	return (result);
}

void	stack_print(t_stack *s, int order)
{
	char	*str_stack;

	ft_printf("-----\nstack: %c\nsize: %d\n-----\n", s->name, s->size);
	str_stack = stack_to_string(s, order);
	ft_printf("%s\n", str_stack);
	free(str_stack);
	ft_printf("-----\n");
}

int	stack_is_sorted(t_stack *s)
{
	t_bi_list	*i;

	i = s->top;
	while (i->prev)
	{
		if (i->content > i->prev->content)
			return (0);
		i = i->prev;
	}
	return (1);
}
