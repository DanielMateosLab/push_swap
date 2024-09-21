/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:43:49 by damateos          #+#    #+#             */
/*   Updated: 2024/09/21 16:41:04 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Sorting algorithm: use merge sort.
- In each iteration we switch the ordering direction.
- We order the groups from top of stack to bottom.
- We use rotations and pushes to sort the groups. Swaps are not used.
- Because we only push in one direction, push time complexity is constant.
- Using a circular buffer, we can also achieve constant complexity for rotations.

5 3 8 6 5 6 1 8
18 56 68 35
8563 8651
13556688
--------------------------
For uneven groups: register werther the uneven group is at the beginning or end.
When calculating the group size, substract one for the first or last group.
5 3 8 7 1 2 6
26 17 38 5
358 1267
...
*/

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int		*stack;
	size_t	capacity;
	size_t	taken;
	size_t	top;
	size_t	base;
	char	name;
}	t_stack;

typedef enum e_direction
{
	PREV,
	NEXT
}	t_direction;

typedef enum e_pointer
{
	BASE,
	TOP
}	t_pointer;

typedef enum e_generic_action
{
	R,
	RR,
	P
}	t_generic_action;

typedef enum e_action
{
	RA,
	RB,
	RRA,
	RRB,
	PA,
	PB
}	t_action;

typedef struct s_sort_state
{
	int				uneven_pos;
	size_t			grp_size;
	t_stack			*from_s;
	t_stack			*to_s;
	int				sort_order;
	t_list			*moves;
}	t_sort_state;

/*
 * Swap the first two elements of the given stack.
 * Does nothing if there are less than two elements.
 */
void	stack_swap(t_stack *stack);
/*
 * Take the first element of stack2 and put it on top of stack1.
 * Does nothing if stack2 is empty or stack1 is full.
 */
void	stack_push(t_stack *stack1, t_stack *stack2);
/*
 * Rotate the stack upwards, moving the first element to the last position.
 */
void	stack_rotate(t_stack *stack);
/*
 * Reverse rotate the stack, moving the last element to the first position.
 */
void	stack_reverse_rotate(t_stack *stack);
void	stack_init_from_nums(t_stack *stack, char **numbers);
void	stack_destroy(t_stack *stack);
void	stack_init_empty(t_stack *stack, int size);
size_t	stack_index(t_stack *stack, size_t index, t_direction direction);
int		stack_is_sorted(t_stack *stack);
size_t	stack_index_n(t_stack *stack, size_t index,
			t_direction direction, size_t count);

#endif
