/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initilizer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void		add_process(t_vm *vm, int pc, t_player *player)
{
	t_process	*process;
	int			i;

	if (((process = ft_memalloc(sizeof(t_process))) == NULL) || \
		((process->reg = ft_memalloc(sizeof(int) * REG_NUMBER)) == NULL))
		die("Error: Out of memory!");
	i = 0;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	process->reg[0] = player->idx;
	process->pc = pc;
	process->carry = 0;
	process->delay = 0;
	process->inst = 0;
	process->vm = vm;
	process->live = 0;
	process->n = vm->p_n++;
	process->player = player;
	process->next = vm->process;
	vm->process = process;
}

void		copy_process(t_vm *vm, t_process *ref)
{
	t_process	*process;
	int			i;

	if (((process = ft_memalloc(sizeof(t_process))) == NULL) || \
		((process->reg = ft_memalloc(sizeof(int) * REG_NUMBER)) == NULL))
		die("Error: Out of memory!");
	i = -1;
	while (++i < REG_NUMBER)
		process->reg[i] = ref->reg[i];
	process->pc = ref->pc;
	process->carry = ref->carry;
	process->delay = ref->delay;
	process->inst = 0;
	process->vm = ref->vm;
	process->live = ref->live;
	process->player = ref->player;
	process->next = vm->process;
	process->n = vm->p_n++;
	vm->process = process;
}

t_codage	*init_codage(void)
{
	int			i;
	t_codage	*ret;

	if ((ret = ft_memalloc(sizeof(t_codage))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->type = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->value = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->raw_value = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	i = 0;
	while (i < 3)
	{
		(ret)->value[i] = 0;
		(ret)->raw_value[i] = 0;
		(ret)->type[i++] = 0;
	}
	(ret)->valid = 1;
	(ret)->to_skip = 2;
	return (ret);
}

void		read_codage_octal(t_codage *codage, int idx, int octal, \
								t_process *pr)
{
	codage->type[idx] = octal;
	if (octal == T_REG)
	{
		codage->raw_value[idx] = (unsigned char)read_bytes(pr->vm,
			next_pc(pr->pc, codage->to_skip), 1) - 1;
		codage->valid = codage->valid && (codage->raw_value[idx] <= 15) && \
		(codage->raw_value[idx] >= 0);
		codage->value[idx] = pr->reg[(unsigned char)(codage->raw_value[idx])];
		codage->to_skip += 1;
	}
	else if (octal == 3)
	{
		codage->raw_value[idx] = (short)read_bytes(pr->vm,
			next_pc(pr->pc, codage->to_skip), 2);
		codage->value[idx] = read_bytes(pr->vm, next_pc(pr->pc,
			((short)codage->raw_value[idx]) % IDX_MOD), 4);
		codage->to_skip += 2;
	}
	else if (octal == T_DIR)
	{
		codage->value[idx] = read_bytes(pr->vm,
			next_pc(pr->pc, codage->to_skip), pr->l_size);
		codage->raw_value[idx] = codage->value[idx];
		codage->to_skip += pr->l_size;
	}
}

t_codage	*read_codage(t_vm *vm, t_process *process, int nf)
{
	t_codage	*ret;
	int			octal;

	ret = vm->codage;
	ret->to_skip = 2;
	ret->valid = 1;
	octal = read_bytes(vm, next_pc(process->pc, 1), 1);
	read_codage_octal(ret, 0, octal >> 6, process);
	ret->valid = ret->valid && (ret->type[0] >= 1) && (ret->type[0] <= 3);
	if (nf > 1)
	{
		read_codage_octal(ret, 1, (octal - (octal & (3 << 6))) >> 4, process);
		ret->valid = ret->valid && (ret->type[1] >= 1) && (ret->type[1] <= 3);
	}
	if (nf > 2)
	{
		read_codage_octal(ret, 2, (octal - (octal & (15 << 4))) >> 2, process);
		ret->valid = ret->valid && (ret->type[2] >= 1) && (ret->type[2] <= 3);
	}
	return (ret);
}
