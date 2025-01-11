/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2025/01/11 15:00:15 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_top_relative_index(t_stack *stack, int number)
{
	int			to_prev_i;
	int			to_next_i;
	t_bi_list	*i;

	to_prev_i = 0;
	i = stack->top;
	if (i->content == number)
		return (0);
	while (i->content != number && i->prev)
	{
		i = i->prev;
		to_prev_i++;
	}
	to_next_i = 1;
	i = stack->base;
	while (i->content != number && i->next)
	{
		i = i->next;
		to_next_i++;
	}
	if (to_prev_i < to_next_i)
		return (to_prev_i * -1);
	return (to_next_i);
}

void	stack_push_all(t_stack *a, t_stack *b, t_list *moves)
{
	while (b->size)
	{
		append_action(P, 'b', &moves);
		stack_push(a, b);
	}
}

int	main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;
	t_list		*moves;

	if (parse_arguments_and_create_stack(argc, argv, &a) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_bzero(&b, sizeof(t_stack));
	a.name = 'a';
	b.name = 'b';
	moves = NULL;
	if (a.size > 1)
	{
		print_moves(moves);
		print_moves_count(moves);
	}
	ft_lstclear(&moves, free);
	stack_destroy(&a);
	stack_destroy(&b);
	return (EXIT_SUCCESS);
}
