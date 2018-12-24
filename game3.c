#include "corewarVM.h"

void	ex_and(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] & codage->value[1];
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
	}
	if (pr->vm->log)
			print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_or(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] | codage->value[1];
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
	}
	if (pr->vm->log)
			print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_xor(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = codage->value[0] ^ codage->value[1];
		pr->carry = (pr->reg[codage->raw_value[2]] == 0);
	}
	if (pr->vm->log)
			print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_ldi(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 2;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[1] != 3) && \
		(codage->type[2] == T_REG))
	{
		pr->reg[codage->raw_value[2]] = read_bytes(pr->vm, next_pc(pr->pc, (codage->value[0] + codage->value[1]) % IDX_MOD), 4);
	}
	if (pr->vm->log)
			print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_sti(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 2;
	codage = read_codage(pr->vm, pr, 3);
	if ((codage->valid == 1) && (codage->type[2] != 3) && \
		(codage->type[0] == T_REG))
	{
		dump_to_mem(pr, 4, codage->value[0], next_pc(pr->pc, (codage->value[1] + codage->value[2]) % IDX_MOD));
	}
	if (pr->vm->log)
		print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}
