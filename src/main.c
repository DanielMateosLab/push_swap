/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2024/12/30 15:12:21 by damateos         ###   ########.fr       */
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

void	init_sort_state(t_sort_state *ss, t_stack *a, t_stack *b)
{
	ss->from_s = a;
	ss->to_s = b;
	ss->sort_order = 1; // Sort order 1 means the top is the smallest
	ss->moves = NULL;
}

void move_stack(t_sort_state *ss, int *arr, size_t len)
{
	int		relative_i;
	size_t	i;
	t_stack	*tmp_stack;

	i = 0;
	if (ss->sort_order == -1)
		reverse_array(arr, len);
	while (i < len)
	{
		// 1. Find the index of the number in the original stack relative to the top
		relative_i = find_top_relative_index(ss->from_s, arr[i]);
		// 2. Rotate or reverse rotate the stack to put the number on top
		while (relative_i != 0)
		{
			if (relative_i > 0)
			{
				append_action(RR, ss->from_s->name, &ss->moves);
				stack_reverse_rotate(ss->from_s);
				relative_i--;
			}
			else
			{
				append_action(R, ss->from_s->name, &ss->moves);
				stack_rotate(ss->from_s);
				relative_i++;
			}
		}
		// 3. Push the number to the destination stack
		append_action(P, ss->from_s->name, &ss->moves);
		stack_push(ss->to_s, ss->from_s);
		i++;
	}
	tmp_stack = ss->from_s;
	ss->from_s = ss->to_s;
	ss->to_s = tmp_stack;
	ss->sort_order *= -1;
}

static void	merge(int *arr, int *temp, size_t left, size_t mid, size_t right)
{
	size_t	i = left;
	size_t	j = mid;
	size_t	k = left;

	while (i < mid && j < right)
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i < mid)
		temp[k++] = arr[i++];
	while (j < right)
		temp[k++] = arr[j++];
}

void	stack_push_all(t_stack *a, t_stack *b, t_list *moves)
{
	while (b->size)
	{
		append_action(P, 'b', &moves);
		stack_push(a, b);
	}
}

t_list	*merge_sort_2(t_stack *a, t_stack *b)
{
	t_sort_state	ss;
	int				*arr_from;
	int				*arr_to;
	size_t			len;
	size_t			size;
	size_t			left;
	size_t			mid;
	size_t			right;
	size_t			i;

	len = a->size;
	size = 1;
	init_sort_state(&ss, a, b);
	arr_from = stack_to_array(a, ss.sort_order);
	arr_to = (int *)ft_calloc(len, sizeof(int));
	while (size < len)
	{
		left = 0;
		while (left < len)
		{
			mid = left + size;
			right = left + 2 * size;
			if (mid > len)
				mid = len;
			if (right > len)
				right = len;
			merge(arr_from, arr_to, left, mid, right);
			left += 2 * size;
		}
		i = 0;
		while (i < len)
		{
			arr_from[i] = arr_to[i];
			i++;
		}
		size *= 2;
		move_stack(&ss, arr_to, len);
	}
	if (!a->size)
		stack_push_all(a, b, ss.moves);
	ft_free((void **)&arr_to);
	ft_free((void **)&arr_from);
	return (ss.moves);
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
		moves = merge_sort_2(&a, &b);
		print_moves(moves);
		print_moves_count(moves);
	}
	ft_lstclear(&moves, free);
	stack_destroy(&a);
	stack_destroy(&b);
	return (EXIT_SUCCESS);
}
