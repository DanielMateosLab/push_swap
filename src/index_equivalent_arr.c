/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_equivalent_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:36:51 by damateos          #+#    #+#             */
/*   Updated: 2024/12/30 18:48:41 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Implementation notes:
 * 4 7 2 1 8 -> source arr
 * 1 2 4 7 8 -> sorted array
 * { 		 -> hashmap of source number to index in sorted array
 *  1: 0
 *  2: 1
 *  4: 2
 *  7: 3
 *  8: 4
 * }
 * 2 3 1 0 4 -> index equivalent array
 */

/** For an int array, returns array where each number is replaced by the index of that number
 * in the original array sorted in descending order.
 */
int *get_index_equivalent_arr(int *arr, size_t len)
{
	t_hashmap	*hm;
	int			*temp_arr;
	int			i;

	temp_arr = ft_int_arr_copy(arr, len);
	ft_int_arr_reverse(temp_arr, len);
	ft_quick_sort(temp_arr, 0, len - 1);
	hm = ft_hm_create(len);
	i = 0;
	while (i < len)
	{
		ft_hm_node_insert(hm, ft_itoa(temp_arr[i]), &i, sizeof(int));
		i++;
	}
	i = 0;
	while (i < len)
	{
		temp_arr[i] = *(int *)ft_hm_get(hm, ft_itoa(arr[i]));
		i++;
	}
	ft_hm_remove(hm);
	return (temp_arr);
}

int *char_arr_to_int_arr(char **arr, size_t len)
{
	int		*int_arr;
	size_t	i;

	int_arr = (int *)ft_calloc(len, sizeof(int));
	if (!int_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		int_arr[i] = ft_atoi(arr[i]);
		i++;
	}
	return (int_arr);
}
