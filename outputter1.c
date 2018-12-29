/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputter1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyerin <iyerin@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:34:06 by iyerin            #+#    #+#             */
/*   Updated: 2018/12/25 19:34:10 by iyerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	print_intro(t_vm *vm)
{
	t_player	*p;

	ft_printf("Introducing contestants...\n");
	p = vm->player;
	while (p != NULL)
	{
		ft_printf("* Player %d,", p->n);
		ft_printf(" weighing %d bytes,", p->size);
		ft_printf(" \"%s\" ", p->name);
		ft_printf("(\"%s\") !\n", p->comment);
		p = p->next;
	}
}

void	dump(t_vm *vm)
{
	int	i;

	if (vm->visual_mode)
		return ;
	if (vm->cycle == vm->nbr_cycles)
	{
		i = 1;
		ft_printf("0x%04x : ", i - 1);
		while (i <= MEM_SIZE)
		{
			ft_printf("%02x ", vm->mem[i - 1]->value);
			if (i % 64 == 0)
			{
				ft_printf("\n");
				if (i < MEM_SIZE)
					ft_printf("0x%04x : ", i);
			}
			i++;
		}
		exit(0);
	}
}
