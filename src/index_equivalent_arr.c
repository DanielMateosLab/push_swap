/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_equivalent_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:36:51 by damateos          #+#    #+#             */
/*   Updated: 2025/01/01 23:02:30 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*create_sorted_arr(int *arr, size_t len)
{
	int		*sorted_arr;
	size_t	i;

	sorted_arr = ft_int_arr_copy(arr, len);
	if (!sorted_arr)
		return (NULL);
	ft_quick_sort(sorted_arr, 0, len - 1);
	return (sorted_arr);
}

t_hashmap	*create_number_to_index_map(int *arr, size_t len)
{
	t_hashmap	*hm;
	int			i;
	t_hm_node	*node;
	char		*key;

	hm = ft_hm_create(len);
	if (!hm)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key = ft_itoa(arr[i]);
		node = ft_hm_node_insert(hm, key, &i, sizeof(int));
		free(key);
		if (!node)
			return (ft_hm_remove(hm), NULL);
		i++;
	}
	return (hm);
}

/** For an int array, returns array where each number is replaced by the index
 * of that number in the original array sorted in ascending order. */
int	*get_index_equivalent_arr(int *arr, size_t len)
{
	t_hashmap	*hm;
	int			*temp_arr;
	int			i;
	char		*key;

	temp_arr = create_sorted_arr(arr, len);
	if (!temp_arr)
		return (NULL);
	hm = create_number_to_index_map(temp_arr, len);
	if (!hm)
		return (ft_free((void **)&temp_arr), NULL);
	i = 0;
	while (i < len)
	{
		key = ft_itoa(arr[i]);
		temp_arr[i] = *(int *)ft_hm_get(hm, key);
		free(key);
		i++;
	}
	ft_hm_remove(hm);
	return (temp_arr);
}

int	*char_arr_to_int_arr(char **arr, size_t len)
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
