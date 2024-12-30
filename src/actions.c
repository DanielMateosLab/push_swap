/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:12:03 by damateos          #+#    #+#             */
/*   Updated: 2024/12/30 15:12:30 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_action	generic_to_named_action(t_generic_action action, char from_name)
{
	t_action	named_action;

	if (from_name == 'a')
	{
		if (action == R)
			named_action = RA;
		else if (action == RR)
			named_action = RRA;
		else
			named_action = PB;
	}
	else
	{
		if (action == R)
			named_action = RB;
		else if (action == RR)
			named_action = RRB;
		else
			named_action = PA;
	}
	return (named_action);
}

t_list	*append_action(t_generic_action action, char from_name, t_list **moves)
{
	t_action	*named_action;
	t_list		*new_move;

	named_action = (t_action *)ft_calloc(1, sizeof(t_action));
	if (!named_action)
		return (ft_lstclear(moves, free), NULL);
	*named_action = generic_to_named_action(action, from_name);
	new_move = ft_lstnew((void *)named_action);
	if (!new_move)
		return (ft_lstclear(moves, free), NULL);
	if (!*moves)
		*moves = new_move;
	else
		ft_lstadd_back(moves, new_move);
	return (*moves);
}
