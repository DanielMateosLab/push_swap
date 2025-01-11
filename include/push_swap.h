/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:43:49 by damateos          #+#    #+#             */
/*   Updated: 2025/01/11 14:27:00 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_bi_list
{
	int					content;
	struct s_bi_list	*next;
	struct s_bi_list	*prev;
}	t_bi_list;


typedef struct s_stack
{
	t_bi_list	*top;
	t_bi_list	*base;
	size_t		size;
	char		name;
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
void	stack_init_from_nums(t_stack *stack, int *numbers, size_t len);
void	stack_destroy(t_stack *stack);
int		stack_is_sorted(t_stack *stack);
char	*stack_to_string(t_stack *stack, int order);
void	stack_print(t_stack *s, int order);
void	print_moves(t_list *moves);
int		*stack_to_array(t_stack *stack, int order);
void	print_moves_count(t_list *moves);
int		parse_arguments_and_create_stack(int argc, char **argv, t_stack *stack);
t_list	*append_action(t_generic_action action, char from_name, t_list **moves);
int		*get_index_equivalent_arr(int *arr, int len);
int		*char_arr_to_int_arr(char **arr, size_t len);

#endif
