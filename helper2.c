#include "corewarVM.h"

unsigned int	read_bytes(t_vm *vm, int pc, unsigned int n_bytes)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < n_bytes)
	{
		res = res * 16 * 16 + vm->mem[next_pc(pc, i++)]->value;
	}
	if (n_bytes == 1)
		res = (unsigned int)((unsigned char)res);
	else if (n_bytes == 2)
		res = (unsigned int)((short)res);
	return (res);
}

void			dump_to_mem(t_process *pr, int len, int val, int idx)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pr->vm->mem[next_pc(idx, i)]->value = (val >> (6 - i * 2));
		pr->vm->mem[next_pc(idx, i)]->player = pr->player;
		pr->vm->mem[next_pc(idx, i)]->last_update = 50;
		val -= ((val >> (6 - i * 2)) << (6 - i * 2));
		i++;
	}
}
