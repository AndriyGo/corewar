#include "corewarVM.h"

void	print_intro(t_vm *vm)
{
	int			i;
	t_player	*p;

	ft_printf(" || PARTICIPANTS: ||\n");
	i = 1;
	p = vm->player;
	while (p)
	{
		ft_printf("=============// Player[%d]\n",i++);
		ft_printf("\tName:    \"%s\"\n", p->name);
		ft_printf("\tWeight:   %d\n", p->size);
		ft_printf("\tComment: \"%s\"\n", p->comment);
		p = p->next;
	}
}

void	dump(t_vm *vm)
{
	int	 i;

	i = 1;
	ft_printf("\n");
	ft_printf(" ||    FIELD:     || \n");
	ft_printf("0x%04x | ", i-1);
	while (i <= MEM_SIZE)
	{
		ft_printf("%02x", vm->mem[i - 1]->value);
		if (i % 64 == 0)
		{
			ft_printf("\n");
			if (i < MEM_SIZE)
				ft_printf("0x%04x | ", i);
		}
		else
			ft_printf(" ");
		i++;
	}
	exit(0);
}