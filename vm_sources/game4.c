/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyerin <iyerin@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:13:47 by iyerin            #+#    #+#             */
/*   Updated: 2018/12/25 19:13:50 by iyerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	ex_lld(t_process *pr)
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
			ft_printf("P %4u | lld %d r%d\n", pr->n, codage->value[0],
				codage->raw_value[1] + 1);
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_lldi(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 2;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[1] != 3) && \
		(codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = read_bytes(pr->vm, next_pc(pr->pc,
			(codage->value[0] + codage->value[1])), 4);
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
		if (pr->vm->log)
		{
			ft_printf("P %4u | lldi %d %d r%d\n", pr->n, codage->value[0],
				codage->value[1], codage->raw_value[2] + 1);
			ft_printf("       | -> load from %d + %d = %d ", codage->value[0],
				codage->value[1], codage->value[0] + codage->value[1]);
			ft_printf("(with pc %d)\n",
				pr->pc + codage->value[0] + codage->value[1]);
		}
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_aff(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 1);
	if ((codage->valid == 1) && (codage->type[0] == T_REG))
	{
		if (!pr->vm->visual_mode && (ft_isprint(codage->raw_value[0])))
		{
			ft_printf("%c", codage->raw_value[0]);
		}
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_lfork(t_process *pr)
{
	short	value;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
	copy_process(pr->vm, pr);
	pr->vm->process->pc = next_pc(pr->pc, value);
	if (pr->vm->log)
		ft_printf("P %4u | lfork %d (%d)\n", pr->n, value,
			pr->pc + value % IDX_MOD);
	pr->pc = next_pc(pr->pc, 3);
}
