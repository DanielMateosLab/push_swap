/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:32:52 by damateos          #+#    #+#             */
/*   Updated: 2024/08/25 11:15:15 by damateos         ###   ########.fr       */
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
	while (*numbers)
	{
		if (!is_number_valid(*numbers))
			return (0);
		numbers++;
	}
	return (1);
}

void	print_array(char **array)
{
	while (*array)
	{
		ft_printf("%s\n", *array);
		array++;
	}
}

int	main(int argc, char **argv)
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
	return (0);
}
