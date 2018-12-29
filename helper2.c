/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyerin <iyerin@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:25:37 by iyerin            #+#    #+#             */
/*   Updated: 2018/12/25 19:25:40 by iyerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

int		read_bytes(t_vm *vm, int pc, unsigned int n_bytes)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	while (i < n_bytes)
	{
		res = res * 16 * 16 + vm->mem[next_pc(pc, i)]->value;
		i++;
	}
	if (n_bytes == 2)
		res = (short)res;
	return (res);
}

void	dump_to_mem(t_process *pr, int len, int val, int idx)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pr->vm->mem[next_pc(idx, i)]->value = ((val & 255 << ((8) *
			(len - i - 1))) >> (8) * (len - i - 1));
		pr->vm->mem[next_pc(idx, i)]->player = pr->player;
		pr->vm->mem[next_pc(idx, i)]->last_update = 50;
		i++;
	}
}

int		process_count(t_vm *vm)
{
	t_process	*tmp;
	int			ret;

	ret = 0;
	tmp = vm->process;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

void	print_command(t_process *pr, int l)
{
	int	i;

	if (pr->vm->log == 0)
		return ;
	i = 0;
	ft_printf("|CMD %05d| = %d (0x%04x -> 0x%04x) ", pr->vm->cycle, l,
		pr->pc, next_pc(pr->pc, l));
	while (i < l)
	{
		ft_printf("%02x ", pr->vm->mem[next_pc(pr->pc, i++)]->value);
	}
	ft_printf("\n");
}

void	print_usage(void)
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles] "
		"[-v] [[-n number] champion1.cor] ...\n");
	ft_printf("   -dump:\n");
	ft_printf("        after nbr_cycles of executions, memory is dumped "
		"on standard output and the game terminates\n");
	ft_printf("   -v:\n");
	ft_printf("        visual mode.\n");
	ft_printf("   -l:\n");
	ft_printf("        log mode.\n");
	ft_printf("   -n:\n");
	ft_printf("        specifies custom player number.\n");
	ft_printf("        IMPORTANT: it is your responsibility to ensure "
		"that number is valid.\n");
	ft_printf("        E.g. a game cannot be played between 2 players "
		"with numbers 1 and 3!\n");
	ft_printf("NOTE: a game must contain between 1 and "
		"%d players!\n", MAX_PLAYERS);
	exit(0);
}
