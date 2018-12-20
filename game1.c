#include "corewarVM.h"

void	load_instruction(t_process *pr)
{
	pr->inst = pr->vm->mem[pr->pc]->value;
	if ((pr->inst < 1) || (pr->inst > 16))
	{
		pr->pc = next_pc(pr->pc, 1);
		pr->inst = 0;
	}
	else if ((pr->inst == 1) || (pr->inst == 4) || (pr->inst == 5) || (pr->inst == 13))
		pr->delay = 10;
	else if ((pr->inst == 2) || (pr->inst == 3))
		pr->delay = 5;
	else if ((pr->inst == 6) || (pr->inst == 7) || (pr->inst == 8))
		pr->delay = 6;
	else if (pr->inst == 9)
		pr->delay = 20;
	else if ((pr->inst == 10) || (pr->inst == 11))
		pr->delay = 25;
	else if (pr->inst == 12)
		pr->delay = 800;
	else if (pr->inst == 14)
		pr->delay = 50;
	else if (pr->inst == 15)
		pr->delay = 1000;
	else if (pr->inst == 16)
		pr->delay = 2;
}

void	tik_process2(t_process *pr)
{
	if (pr->inst == 10)
		ex_ldi(pr);
	else if (pr->inst == 11)
		ex_sti(pr);
	else if (pr->inst == 12)
		ex_fork(pr);
	else if (pr->inst == 13)
		ex_lld(pr);
	else if (pr->inst == 14)
		ex_lldi(pr);
	else if (pr->inst == 15)
		ex_lfork(pr);
	else if (pr->inst == 1)
		ex_aff(pr);
}

void	tik_process(t_process *pr)
{
	if (pr->inst == 0)
		load_instruction(pr);
	else if (pr->delay > 0)
		pr->delay = pr->delay - 1;
	else if (pr->inst == 1)
		ex_live(pr);
	else if (pr->inst == 2)
		ex_load(pr);
	else if (pr->inst == 3)
		ex_st(pr);
	else if (pr->inst == 4)
		ex_add(pr);
	else if (pr->inst == 5)
		ex_sub(pr);
	else if (pr->inst == 6)
		ex_and(pr);
	else if (pr->inst == 7)
		ex_or(pr);
	else if (pr->inst == 8)
		ex_xor(pr);
	else if (pr->inst == 9)
		ex_zjmp(pr);
	else
		tik_process2(pr);
}

void	ex_live(t_process *pr)
{
	unsigned int	value;
	t_player		*tmp;

	value = read_bytes(pr->vm, next_pc(pr->pc, 1), 4);
	pr->live = 1;
	tmp = pr->vm->player;
	while (tmp != NULL)
	{
		if (tmp->idx == (int)value)
		{
			tmp->lives += 1;
			tmp->last_live = pr->vm->cycle;
			break;
		}
		tmp = tmp->next;
	}
	pr->pc = next_pc(pr->pc, 5);
}

void	ex_zjmp(t_process *pr)
{
	short	value;

	if (pr->carry == 1)
	{
		value = read_bytes(pr->vm, next_pc(pr->pc, 1), 2);
		pr->pc = next_pc(pr->pc, value % IDX_MOD);
	}
	else
		pr->pc = next_pc(pr->pc, 3);
}
