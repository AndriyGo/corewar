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

void	tik_process(t_process *pr)
{
	if (pr->inst == 0)
		load_instruction(pr);
	else if (pr->delay > 0)
		pr->delay = pr->delay - 1;
	else if (pr->inst == 1)
		
}