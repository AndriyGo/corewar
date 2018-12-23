#include "corewarVM.h"

void	ex_and(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] & codage->value[1];
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}

void	ex_or(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] | codage->value[1];
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}

void	ex_xor(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] ^ codage->value[1];
		pr->carry = (pr->carry + 1) % 2;
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}

void	ex_ldi(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 2;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[1] != T_IND) && \
		(codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = read_bytes(pr->vm, next_pc(pr->pc, (codage->value[0] + codage->value[1]) % IDX_MOD), 4);
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}

void	ex_sti(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 2;
	codage = read_codage(pr->vm, pr, 3);
	//ft_printf("%d %d\n%d %d\n %d %d!\n", codage->raw_value[0], codage->value[0], codage->raw_value[1], codage->value[1], codage->raw_value[2], codage->value[2]);
	if ((codage->valid == 1) && (codage->type[2] != T_IND) && \
		(codage->type[0] == T_REG))
	{
		dump_to_mem(pr, 4, codage->value[0], next_pc(pr->pc, (codage->value[1] + codage->value[2]) % IDX_MOD));
	}
	pr->pc = next_pc(pr->pc, codage->to_skip);
	free(codage->type);
	free(codage->value);
	free(codage->raw_value);
	free(codage);
}
