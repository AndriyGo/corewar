#include "corewarVM.h"

unsigned int	read_bytes(t_vm *vm, int pc, unsigned int n_bytes)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < n_bytes)
	{
		ft_printf("%d\n", vm->mem[next_pc(pc, i++)]->value);
		res = res * 16 * 16 + vm->mem[next_pc(pc, i)]->value;
		i++;
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
		pr->vm->mem[next_pc(idx, i)]->value = ((val & 255 << ((8) * (len - i - 1))) >> (8) * (len - i - 1));
		pr->vm->mem[next_pc(idx, i)]->player = pr->player;
		pr->vm->mem[next_pc(idx, i)]->last_update = 50;
		i++;
	}
}
