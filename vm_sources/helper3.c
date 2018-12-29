/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

int		count_players(t_vm *vm)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = vm->player;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	if (i > MAX_PLAYERS)
		die("Error: Max number of players exceeded!");
	return (i);
}

void	set_player_indexes(t_vm *vm)
{
	t_player	*tmp;
	int			i;

	i = -1;
	tmp = vm->player;
	while (tmp != NULL)
	{
		tmp->idx = i;
		tmp->n = -i--;
		tmp = tmp->next;
	}
}

void	sort_players(t_vm *vm)
{
	t_player	*tmp;
	t_player	*tmp2;
	int			i;

	tmp = vm->player;
	i = 0;
	die_if_p_index_sucks(vm);
	while (tmp != NULL)
	{
		i++;
		if ((tmp->idx > 0) && (tmp->idx != i))
		{
			i = 1;
			tmp2 = vm->player;
			while (i++ < tmp->idx)
				tmp2 = tmp2->next;
			tmp->next = tmp2->next;
			tmp2->next = tmp;
			tmp = vm->player;
			i = 0;
		}
		else
			tmp = tmp->next;
	}
	set_player_indexes(vm);
}

void	delete_process(t_process **p, t_process *next, t_process **del)
{
	*p = next;
	free((*del)->reg);
	free(*del);
}

void	remove_dead_p(t_vm *vm)
{
	t_process	*tmp;
	t_process	*prev;

	prev = NULL;
	tmp = vm->process;
	while (tmp)
	{
		if ((tmp->live == 0) && (prev == NULL))
		{
			delete_process(&(vm->process), tmp->next, &tmp);
			tmp = vm->process;
		}
		else if (tmp->live == 0)
		{
			delete_process(&tmp, tmp->next, &(prev->next));
			prev->next = tmp;
		}
		else
		{
			tmp->live = 0;
			prev = tmp;
			tmp = tmp->next;
		}
	}
	vm->game_on = (vm->process != NULL);
}
