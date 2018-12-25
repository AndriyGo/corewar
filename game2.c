#include "corewarVM.h"

void	ex_fork(t_process *pr)
{
	short	value;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
	copy_process(pr->vm, pr);
	pr->vm->process->pc = next_pc(pr->pc, value % IDX_MOD);
	print_command(pr, 3);
	pr->pc = next_pc(pr->pc, 3);
}

void	ex_load(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	ft_printf("1");
	codage = read_codage(pr->vm, pr, 2);
	ft_printf("2");
	if ((codage->valid == 1) && ((codage->type[0] == T_DIR) || \
		(codage->type[0] == 3)) && (codage->type[1] == T_REG))
	{
		pr->reg[codage->raw_value[1]] = codage->value[0];
		pr->carry = (pr->reg[codage->raw_value[1]] == 0);
	}
	print_command(pr, codage->to_skip);
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
			pr->reg[codage->raw_value[1]] = codage->value[0];
		else
			dump_to_mem(pr, 4, codage->value[0], next_pc(pr->pc, codage->value[1]));
	}
	print_command(pr, codage->to_skip);
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
	}
	print_command(pr, codage->to_skip);
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
	}
	print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}
