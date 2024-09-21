/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2024/09/21 16:57:47 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_number_valid(char *number)
{
	if (*number == '-' || *number == '+')
		number++;
	while (*number)
	{
		if (!ft_isdigit(*number))
			return (0);
		number++;
	}
	return (1);
}

// We add 1 to the size because the string might begin with a symbol
int	is_number_in_int_range(char *number)
{
	int		max_length;
	int		n;
	long	number_as_long;

	max_length = 1;
	n = INT_MIN;
	while (n != 0)
	{
		max_length++;
		n /= 10;
	}
	if (ft_strlen(number) > (size_t)max_length)
		return (0);
	number_as_long = ft_atol(number);
	if (number_as_long < INT_MIN || number_as_long > INT_MAX)
		return (0);
	return (1);
}

int	are_numbers_valid(char **numbers)
{
	t_hashmap	*hm;
	int			true;

	true = 1;
	hm = ft_hm_create(str_array_len(numbers));
	while (*numbers)
	{
		if (ft_hm_get(hm, *numbers) || !is_number_valid(*numbers)
			|| !is_number_in_int_range(*numbers))
		{
			ft_hm_remove(hm);
			return (0);
		}
		ft_hm_node_insert(hm, *numbers, &true, sizeof(int));
		numbers++;
	}
	ft_hm_remove(hm);
	return (1);
}

/**
 * Validates and parses the arguments. Returns boolean that indicates
 * if an error occurred.
 * - If the arguments are invalid, prints Error\n to stderr and returns
 * EXIT_FAILURE.
 * - If empty args prints nothing and returns EXIT_FAILURE.
 * - If valid arguments and unsorted array, returns a stack with the integers.
 */
int	parse_arguments_and_create_stack(int argc, char **argv, t_stack *stack)
{
	char	**numbers;

	if (argc < 2)
		return (EXIT_FAILURE);
	if (argc == 2)
	{
		if (ft_strlen(argv[1]) == 0)
			return (EXIT_FAILURE);
		numbers = ft_split(argv[1], ' ');
	}
	else
		numbers = str_array_copy_n(argv + 1, argc - 1);
	if (!are_numbers_valid(numbers) || !str_array_len(numbers))
		return (write(STDERR_FILENO, "Error\n", 6),
			str_array_clear(numbers), EXIT_FAILURE);
	stack_init_from_nums(stack, numbers);
	return (EXIT_SUCCESS);
}

t_action	generic_to_named_action(t_generic_action action, char from_name)
{
	t_action	named_action;

	if (from_name == 'a')
	{
		if (action == R)
			named_action = RA;
		else if (action == RR)
			named_action = RRA;
		else if (action == P)
			named_action = PB;
	}
	else
	{
		if (action == R)
			named_action = RB;
		else if (action == RR)
			named_action = RRB;
		else if (action == P)
			named_action = PA;
	}
	return (named_action);
}

t_list	*append_action(t_generic_action action, char from_name, t_list **moves)
{
	t_action	named_action;
	t_list		*new_move;

	named_action = generic_to_named_action(action, from_name);
	new_move = ft_lstnew(named_action);
	if (!new_move)
		return (ft_lstclear(moves, free), NULL);
	if (!*moves)
		*moves = new_move;
	else
		ft_lstadd_back(moves, new_move);
	return (*moves);
}

int	find_top_relative_index(t_stack *stack, int number)
{
	int	i;

	i = 0;
	while (i < stack->taken)
	{
		if (stack->stack[stack_index_n(stack, stack->top, PREV, i)] == number)
			return (i * -1);
		if (stack->stack[stack_index_n(stack, stack->top, NEXT, i)] == number)
			return (i);
		i++;
	}
	return (0);
}

void	sort_group(t_sort_state *ss, size_t grp_size)
{
	int		*nums;
	size_t	i;
	// if relative_i is negative, we have to reverse rotate,
	// if positive, we have to rotate
	int		relative_i;

	nums = (int *)ft_calloc(grp_size, sizeof(int));
	if (!nums)
		return (free(nums), exit(EXIT_FAILURE));
	i = 0;
	while (i < grp_size)
	{
		nums[i] = ss->from_s->stack[
			stack_index_n(ss->from_s, ss->from_s->top, PREV, i)];
		i++;
	}
	ft_quick_sort(nums, 0, grp_size - 1);
	if (ss->sort_order == -1)
		ft_reverse_order(nums, 0, grp_size - 1);
	i = 0;
	while (i < grp_size)
	{
		// 1. Find the index of the number in the original stack relative to the top
		relative_i = find_top_relative_index(ss->from_s, nums[i]);
		// 2. Rotate or reverse rotate the stack to put the number on top
		while (relative_i != 0)
		{
			if (relative_i > 0)
			{
				append_action(R, ss->from_s->name, &ss->moves);
				stack_rotate(ss->from_s);
				relative_i--;
			}
			else
			{
				append_action(RR, ss->from_s->name, &ss->moves);
				stack_reverse_rotate(ss->from_s);
				relative_i++;
			}
		}
		// 3. Push the number to the destination stack
		append_action(P, ss->from_s->name, &ss->moves);
		stack_push(ss->to_s, ss->from_s);
	}
	free(nums);
}

void	merge_groups_adjusting_grp_size(t_sort_state *ss, size_t grp_size)
{
	size_t	group_count;
	size_t	i;

	group_count = ss->from_s->taken / grp_size
		+ (ss->from_s->taken % grp_size != 0);
	i = 0;
	while (i < group_count)
	{
		if (i == 0 && ss->uneven_pos == -1)
			sort_group(ss, grp_size - 1);
		else if (i == group_count - 1 && ss->uneven_pos == 1)
			sort_group(ss, grp_size - 1);
		else
			sort_group(ss, grp_size);
		i++;
	}
}

void	init_sort_state(t_sort_state *ss, t_stack *a, t_stack *b)
{
	if (a->capacity % 2 == 0)
		ss->uneven_pos = 0;
	else
		ss->uneven_pos = -1;
	ss->from_s = a;
	ss->to_s = b;
	ss->sort_order = 1;
}

t_list	*merge_sort(t_stack *a, t_stack *b)
{
	t_sort_state	ss;
	t_stack			*tmp_stack;
	size_t			grp_size;

	init_sort_state(&ss, a, b);
	grp_size = 2;
	while (!stack_is_sorted(ss.from_s))
	{
		merge_groups_adjusting_grp_size(&ss, grp_size);
		grp_size *= 2;
		if (grp_size > ss.from_s->capacity)
			grp_size = ss.from_s->capacity;
		if (ss.uneven_pos != 0)
			ss.uneven_pos *= -1;
		tmp_stack = ss.from_s;
		ss.from_s = ss.to_s;
		ss.to_s = tmp_stack;
		ss.sort_order *= -1;

	}
	return (ss.moves);
}
/* TODO: When reversing a stack order, loop with rotate + push*/

int	main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;
	t_list		*moves;

	if (parse_arguments_and_create_stack(argc, argv, &a) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	stack_init_empty(&b, a.capacity);
	a.name = 'a';
	b.name = 'b';
	moves = merge_sort(&a, &b);
	stack_destroy(&a);
	stack_destroy(&b);
}
