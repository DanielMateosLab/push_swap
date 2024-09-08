/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2024/09/08 19:41:34 by damateos         ###   ########.fr       */
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

int	are_numbers_valid(char **numbers)
{
	t_hashmap	*hm;
	int			true;

	true = 1;
	hm = ft_hm_create(str_array_len(numbers));
	while (*numbers)
	{
		if (ft_hm_get(hm, *numbers) || !is_number_valid(*numbers))
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
	// TODO: fix leaks e2e test
	(void)stack;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_stack	a;

	if (parse_arguments_and_create_stack(argc, argv, &a) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
