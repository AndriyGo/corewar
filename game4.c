#include "corewarVM.h"

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
	}
	print_command(pr, codage->to_skip);
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
		pr->reg[codage->raw_value[2]] = read_bytes(pr->vm, next_pc(pr->pc, (codage->value[0] + codage->value[1])), 4);
	}
	print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_aff(t_process *pr)
{
	t_codage		*codage;

	pr->l_size = 4;
	codage = read_codage(pr->vm, pr, 1);
	if ((codage->valid == 1) && (codage->type[0] == T_REG))
	{
		ft_printf("%c", codage->value[0]);
	}
	print_command(pr, codage->to_skip);
	pr->pc = next_pc(pr->pc, codage->to_skip);
}

void	ex_lfork(t_process *pr)
{
	short	value;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
	copy_process(pr->vm, pr);
	pr->vm->process->pc = (pr->vm->process->pc + value) % MEM_SIZE;
	print_command(pr, 3);
	pr->pc = next_pc(pr->pc, 3);
}
