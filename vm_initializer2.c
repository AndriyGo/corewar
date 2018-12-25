#include "corewarVM.h"

void		add_process(t_vm *vm, int pc, t_player *player)
{
	t_process	*process;
	t_process	*tmp;
	int			i;

	ft_printf("pr 1\n");
	if (((process = ft_memalloc(sizeof(t_process))) == NULL) || \
		((process->reg = ft_memalloc(REG_NUMBER * sizeof(int))) == NULL))
		die("Error: Out of memory!");
	ft_printf("pr 2\n");
	i = 0;
	while (i < REG_NUMBER)
		process->reg[i++] = 0;
	process->reg[0] = player->idx;
	process->pc = pc;
	process->carry = 0;
	process->delay = 0;
	process->inst = 0;
	process->vm = vm;
	process->live = 0;
	process->player = player;
	process->next = NULL;
	if (vm->process == NULL)
		vm->process = process;
	else
	{
		tmp = vm->process;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = process;
	}
}

void		copy_process(t_vm *vm, t_process *ref)
{
	t_process	*process;
	int			i;

	if (((process = ft_memalloc(sizeof(t_process))) == NULL) || \
		((process->reg = ft_memalloc(REG_NUMBER * sizeof(int))) == NULL))
		die("Error: Out of memory!");
	i = -1;
	while (++i < REG_NUMBER)
		process->reg[i] = ref->reg[i];
	process->pc = ref->pc;
	process->carry = ref->carry;
	process->delay = ref->delay;
	process->inst = 0;
	process->vm = ref->vm;
	process->live = ref->live;
	process->player = ref->player;
	process->next = vm->process;
	vm->process = process;
}

t_codage	*init_codage()
{
	int	i;
	t_codage	*ret;

	if ((ret = ft_memalloc(sizeof(t_codage))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->type = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->value = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	if (((ret)->raw_value = ft_memalloc(3 * sizeof(int))) == NULL)
		die("Error: Out of memory!");
	i = 0;
	while (i < 3)
	{
		(ret)->value[i] = 0;
		(ret)->raw_value[i] = 0;
		(ret)->type[i++] = 0;
	}
	(ret)->valid = 1;
	(ret)->to_skip = 2;
	return (ret);
}

void		read_codage_octal(t_codage *codage, int idx, int octal, t_process *pr)
{
	codage->type[idx] = octal;
	if (octal == T_REG)
	{
		codage->raw_value[idx] = (unsigned char)read_bytes(pr->vm, next_pc(pr->pc, codage->to_skip), 1) - 1;
		if ((codage->raw_value[idx] < 0) || (codage->raw_value[idx] > 15))
			codage->valid = 0;
		codage->value[idx] = pr->reg[(unsigned char)(codage->raw_value[idx])];
		codage->to_skip += 1;
	}
	else if (octal == 3)
	{
		codage->raw_value[idx] = (short)read_bytes(pr->vm, next_pc(pr->pc, codage->to_skip), 2);
		codage->value[idx] = read_bytes(pr->vm, next_pc(pr->pc, ((short)codage->raw_value[idx]) % IDX_MOD), 4);
		codage->to_skip += 2;
	}
	else if (octal == T_DIR)
	{
		codage->value[idx] = read_bytes(pr->vm, next_pc(pr->pc, codage->to_skip), pr->l_size);
		if (pr->l_size == 2)
			codage->value[idx] = (short)codage->value[idx];
		codage->raw_value[idx] = codage->value[idx];
		codage->to_skip += pr->l_size;
	}
	else
		codage->valid = 0;
}

t_codage	*read_codage(t_vm *vm, t_process *process, int nf)
{
	t_codage	*ret;
	int			octal;

	ret = vm->codage;
	ret->to_skip = 2;
	ret->valid = 1;
	ft_printf("\n1");
	octal = read_bytes(vm, next_pc(process->pc, 1), 1);
	ft_printf("\n2");
	read_codage_octal(ret, 0, octal >> 6, process);
	ft_printf("\n3");
	if (nf > 1)
		read_codage_octal(ret, 1, (octal - (octal & (3 << 6))) >> 4, process);
	if (nf > 2)
		read_codage_octal(ret, 2, (octal - (octal & (15 << 4))) >> 2, process);
	return (ret);
}
