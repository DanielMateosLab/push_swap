/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:01:16 by damateos          #+#    #+#             */
/*   Updated: 2024/09/22 17:20:07 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*stack_to_string(t_stack *stack, int order)
{
	char			*result;
	t_bi_list		*i;
	char			*num_str;

	result = ft_strdup("");
	if (order == 1)
		i = stack->base;
	else
		i = stack->top;
	while (i)
	{
		num_str = ft_itoa(*(int *)i->content);
		result = ft_strjoin(result, num_str);
		free(num_str);
		result = ft_strjoin(result, " ");
		if (order == 1)
			i = i->next;
		else
			i = i->prev;
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
			break ;
		i = i->prev;
	}
	i = s->top;
	while (i->prev)
	{
		if (i->content < i->prev->content)
			return (0);
		i = i->prev;
	}
	return (1);
}
