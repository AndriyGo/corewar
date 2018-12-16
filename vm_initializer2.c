#include "corewarVM.h"

void	add_process(t_vm *vm, int pc)
{
	t_process	*process;
	int			i;
	t_process	*tmp;

	if (((process = ft_memalloc(sizeof(t_process))) == NULL) || \
		((process->regs = ft_memalloc(REG_NUMBER * sizeof(int))) == NULL))
		die("Error: Out of memory!");
	i = 0;
	while (i < REG_NUMBER)
		process->regs[i++] = 0;
	process->pc = pc;
	process->carry = 0;
	process->delay = 0;
	process->inst = 0;
	process->vm = vm;
	process->live = 0;
	if (vm->process == NULL)
		vm->process = process;
	else
	{
		tmp = vm->process;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = process;
	}
}
