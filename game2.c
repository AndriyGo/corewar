#include "corewarVM.h"

void	ex_fork(t_process *pr)
{
	unsigned int	value;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
	copy_process(pr->vm, pr);
	pr->vm->process->pc = value % IDX_MOD;
	pr->pc = next_pc(pr->pc, 3);
}

void	ex_load(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 2);
	if ((codage->valid == 1) && ((codage->type[0] == T_DIR) || \
		(codage->type[0] == T_IND)) && (codage->type[1] == T_REG))
	{
		pr->reg[codage->raw_value[1]] = codage->value[0];
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}

void	ex_st(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 2);
	if ((codage->valid == 1) && ((codage->type[1] == T_IND) || \
		(codage->type[1] == T_REG)) && (codage->type[0] == T_REG))
	{
		if (codage->type[1] == T_REG)
			pr->reg[codage->raw_value[1]] = codage->value[0];
		else
			dump_to_mem(pr, 4, codage->value[0], next_pc(pr->pc, codage->value[1]));
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
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
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
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
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}
