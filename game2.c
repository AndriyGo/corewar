/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyerin <iyerin@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:10:56 by iyerin            #+#    #+#             */
/*   Updated: 2018/12/25 19:11:02 by iyerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	ex_fork(t_process *pr)
{
	short	value;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
	copy_process(pr->vm, pr);
	pr->vm->process->pc = next_pc(pr->pc, value % IDX_MOD);
	if (pr->vm->log)
		ft_printf("P %4u | fork %d (%d)\n", pr->n, value,
			pr->pc + (value % IDX_MOD));
	pr->pc = next_pc(pr->pc, 3);
}

void	ex_load(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 2);
	if ((codage->valid == 1) && ((codage->type[0] == T_DIR) || \
		(codage->type[0] == 3)) && (codage->type[1] == T_REG))
	{
		pr->reg[codage->raw_value[1]] = codage->value[0];
		pr->carry = (pr->reg[codage->raw_value[1]] == 0);
		if (pr->vm->log)
			ft_printf("P %4u | ld %d r%d\n", pr->n, codage->value[0],
				codage->raw_value[1] + 1);
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_st(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 2);
	if ((codage->valid == 1) && ((codage->type[1] == 3) || \
		(codage->type[1] == T_REG)) && (codage->type[0] == T_REG))
	{
		if (codage->type[1] == T_REG)
		{
			pr->reg[codage->raw_value[1]] = codage->value[0];
			if (pr->vm->log)
				ft_printf("P %4u | st r%d %d\n", pr->n,
					codage->raw_value[0] + 1, codage->raw_value[1] + 1);
		}
		else
		{
			dump_to_mem(pr, 4, codage->value[0],
				next_pc(pr->pc, codage->raw_value[1] % IDX_MOD));
			if (pr->vm->log)
				ft_printf("P %4u | st r%d %d\n", pr->n,
					codage->raw_value[0] + 1, codage->raw_value[1]);
		}
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_add(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[0] == T_REG) && \
		(codage->type[1] == T_REG) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] + codage->value[1];
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
		if (pr->vm->log)
			ft_printf("P %4u | add r%d r%d r%d\n", pr->n,
				codage->raw_value[0] + 1, codage->raw_value[1] + 1,
				codage->raw_value[2] + 1);
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_sub(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[0] == T_REG) && \
		(codage->type[1] == T_REG) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] - codage->value[1];
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
		if (pr->vm->log)
			ft_printf("P %4u | sub r%d r%d r%d\n", pr->n,
				codage->raw_value[0] + 1, codage->raw_value[1] + 1,
				codage->raw_value[2] + 1);
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}
