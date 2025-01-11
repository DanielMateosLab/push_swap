/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:04:00 by damateos          #+#    #+#             */
/*   Updated: 2025/01/11 14:39:49 by damateos         ###   ########.fr       */
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

char	**create_numbers_str_arr(int argc, char **argv)
{
	char	**numbers;

	if (argc < 2)
		return (NULL);
	if (argc == 2)
	{
		if (ft_strlen(argv[1]) == 0)
			return (NULL);
		numbers = ft_split(argv[1], ' ');
	}
	else
		numbers = str_array_copy_n(argv + 1, argc - 1);
	return (numbers);
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
	int		*int_arr;
	int		*index_arr;

	numbers = create_numbers_str_arr(argc, argv);
	if (!numbers)
		return (EXIT_FAILURE);
	if (!are_numbers_valid(numbers) || !str_array_len(numbers))
		return (write(STDERR_FILENO, "Error\n", 6),
			str_array_clear(numbers), EXIT_FAILURE);
	int_arr = char_arr_to_int_arr(numbers, argc - 1);
	str_array_clear(numbers);
	if (!int_arr)
		return (EXIT_FAILURE);
	index_arr = get_index_equivalent_arr(int_arr, argc - 1);
	ft_free((void **)&int_arr);
	if (!index_arr)
		return (EXIT_FAILURE);
	stack_init_from_nums(stack, index_arr, argc - 1);
	ft_free((void **)&index_arr);
	return (EXIT_SUCCESS);
}
