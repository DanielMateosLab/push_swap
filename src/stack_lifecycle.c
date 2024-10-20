/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:44:20 by damateos          #+#    #+#             */
/*   Updated: 2024/10/18 13:32:14 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bi_list	*ft_bi_lst_new(int content)
{
	t_bi_list	*new;

	new = (t_bi_list *)ft_calloc(1, sizeof(t_bi_list));
	if (!new)
		return (NULL);
	new->content = content;
	return (new);
}

/** Initializes the stack with the given numbers. The first number
 * is the top of the stack.
 */
void	stack_init_from_nums(t_stack *stack, char **numbers)
{
	ssize_t		i;
	t_bi_list	*new;
	t_bi_list	*prev;
	int			num;

	stack->size = str_array_len(numbers);
	i = (ssize_t)stack->size - 1;
	num = ft_atoi(numbers[i]);
	stack->base = ft_bi_lst_new(num);
	stack->top = stack->base;
	prev = stack->base;
	while (i--)
	{
		num = ft_atoi(numbers[i]);
		new = ft_bi_lst_new(num);
		ft_lstadd_back((t_list **)&prev, (t_list *)new);
		new->prev = prev;
		prev = new;
		if (i == 0)
			stack->top = new;
	}
}

void	stack_destroy(t_stack *stack)
{
	ft_lstclear((t_list **)&stack->base, NULL);
	stack->base = NULL;
	stack->top = NULL;
	stack->size = 0;
}
