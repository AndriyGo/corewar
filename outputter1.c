#include "corewarVM.h"

void	dump(t_vm *vm)
{
	int	 i;

	i = 1;
	while (i <= MEM_SIZE)
	{
		ft_printf("%c", vm->mem[i - 1]->value);
		if (i % 64 == 0)
			ft_printf("\n");
		else if (i % 2 == 0)
			ft_printf(" ");
		i++;
	}
	exit(0);
}