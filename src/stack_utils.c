/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:01:16 by damateos          #+#    #+#             */
/*   Updated: 2024/12/30 18:27:39 by damateos         ###   ########.fr       */
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
		i = stack->top;
	else
		i = stack->base;
	while (i)
	{
		num_str = ft_itoa(i->content);
		result = ft_strjoin(result, num_str);
		free(num_str);
		result = ft_strjoin(result, " ");
		if (order == 1)
			i = i->prev;
		else
			i = i->next;
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

void	print_move(void *content)
{
	t_action	*move;

	move = (t_action *)content;
	if (*move == RA)
		ft_printf("RA ");
	else if (*move == RB)
		ft_printf("RB ");
	else if (*move == RRA)
		ft_printf("RRA ");
	else if (*move == RRB)
		ft_printf("RRB ");
	else if (*move == PA)
		ft_printf("PA ");
	else if (*move == PB)
		ft_printf("PB ");
}

void	print_moves(t_list *moves)
{
	ft_lstiter(moves, print_move);
	ft_printf("\n");
}

void	print_moves_count(t_list *moves)
{
	size_t	count;

	count = 0;
	while (moves)
	{
		count++;
		moves = moves->next;
	}
	ft_printf("moves count: %d\n", (int)count);
}
