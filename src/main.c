/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2024/09/20 22:11:25 by damateos         ###   ########.fr       */
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

void	merge_groups(t_stack *from, t_stack *to,
			size_t group_size, int uneven_pos)
{

}

void	merge_sort(t_stack *a, t_stack *b)
{
	int				uneven_pos;
	size_t			group_size;
	t_stack			*from_stack;
	t_stack			*to_stack;
	t_stack			*tmp_stack;

	if (a->capacity % 2 == 0)
		uneven_pos = 0;
	else
		uneven_pos = -1;
	group_size = 2;
	from_stack = a;
	to_stack = b;
	while (!stack_is_sorted(&from_stack))
	{
		merge_groups(from_stack, to_stack, group_size, uneven_pos);
		group_size *= 2;
		if (group_size > from_stack->capacity)
			group_size = from_stack->capacity;
		if (uneven_pos != 0)
			uneven_pos *= -1;
		tmp_stack = from_stack;
		from_stack = to_stack;
		to_stack = tmp_stack;
	}
}
/* TODO: When reversing a stack order, loop with rotate + push*/

int	main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;

	if (parse_arguments_and_create_stack(argc, argv, &a) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	stack_init_empty(&b, a.capacity);
	merge_sort(&a, &b);
	stack_destroy(&a);
	stack_destroy(&b);
}
