/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	die_if_p_index_sucks(t_vm *vm)
{
	int			c;
	t_player	*tmp;

	c = count_players(vm);
	tmp = vm->player;
	while (tmp != NULL)
	{
		if (tmp->idx > c)
			die("Error: Player index cannot exceed players count!");
		tmp = tmp->next;
	}
}

void	decrease_cycle_to_die(t_vm *vm)
{
	t_player	*p;

	if ((vm->checks == 0) || (vm->lives >= NBR_LIVE))
	{
		vm->checks = MAX_CHECKS;
		vm->cycle_to_die -= CYCLE_DELTA;
	}
	vm->lives = 0;
	p = vm->player;
	while (p)
	{
		p->lives = 0;
		p = p->next;
	}
}
