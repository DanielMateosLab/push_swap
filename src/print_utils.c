/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:37:52 by damateos          #+#    #+#             */
/*   Updated: 2025/01/11 22:37:55 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_move(void *content)
{
	t_action	*move;

	move = (t_action *)content;
	if (*move == RA)
		ft_printf("RA ");
	else if (*move == RB)
		ft_printf("RB ");
	else if (*move == RRA)
		ft_printf("RRA ");
	else if (*move == RRB)
		ft_printf("RRB ");
	else if (*move == PA)
		ft_printf("PA ");
	else if (*move == PB)
		ft_printf("PB ");
}

void	print_moves(t_list *moves)
{
	ft_lstiter(moves, print_move);
	ft_printf("\n");
}

void	print_moves_count(t_list *moves)
{
	size_t	count;

	count = 0;
	while (moves)
	{
		count++;
		moves = moves->next;
	}
	ft_printf("moves count: %d\n", (int)count);
}
