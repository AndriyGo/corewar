#include "corewarVM.h"

int	read_bytes(t_vm *vm, int pc, unsigned int n_bytes)
{
	unsigned int	i;
	int	res;

	i = 0;
	res = 0;
	while (i < n_bytes)
	{
		//ft_printf("%d\n", vm->mem[next_pc(pc, i++)]->value);
		res = res * 16 * 16 + vm->mem[next_pc(pc, i)]->value;
		i++;
	}
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

int				process_count(t_vm *vm)
{
	t_process	*tmp;
	int			ret;

	ret = 0;
	tmp = vm->process;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

void			print_command(t_process *pr, int l)
{
	int	i;

	if (pr->vm->log ==0)
		return ;
	i = 0;
	ft_printf("|CMD| = %d (0x%04x -> 0x%04x) ",l, pr->pc, next_pc(pr->pc, l));
	while (i < l)
	{
		ft_printf("%02x ", pr->vm->mem[next_pc(pr->pc, i++)]->value);
	}
	ft_printf("\n");
}
