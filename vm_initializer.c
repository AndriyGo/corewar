#include "corewarVM.h"

void	create_vm(t_vm **vm)
{
	int	i;

	if ((*vm = ft_memalloc(sizeof(t_vm))) == NULL)
		die("Error: Out of memory!");
	(*vm)->cycle = 0;
	(*vm)->cycle_to_die = CYCLE_TO_DIE;
	(*vm)->process = NULL;
	(*vm)->player = NULL;
	if (((*vm)->mem = ft_memalloc(MEM_SIZE * sizeof(char))) == NULL)
		die("Error: Out of memory!");
	i = 0;
	while (i < MEM_SIZE)
		(*vm)->mem[i++] = 0;
}

void	create_player(t_player **p, char *filename)
{
	int		fd;
	int		i;
	char	c;
	char	r;

	if ((fd = open(filename, O_RDONLY)) == -1)
		die("Error: Cannot open champion file!");
	
}