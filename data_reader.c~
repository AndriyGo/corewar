#include "corewarVM.h"

int		player_index(int i, int argc, char **argv)
{
	char	*num;
	char	*tmp;
	int		j;
	int		idx;

	if (i == argc)
		print_usage();
	num = argv[i];
	tmp = num;
	j = 0;
	while (*tmp)
	{
		if (!(((*tmp == '+') && (j == 0)) || ft_isdigit(*tmp)))
			die("Error: player index must be a valid number!");
		tmp++;
		j++;
	}
	idx = ft_atoi(num);
	if (idx < 1)
		die("Error: player index must be greater or equal to 1");
	return (idx);
}

void	read_dump(t_vm *vm, int i, int argc, char **argv)
{
	char	*num;
	char	*tmp;
	int		j;

	if (i == argc)
		print_usage();
	num = argv[i];
	tmp = num;
	j = 0;
	while (*tmp)
	{
		if (!(((*tmp == '+') && (j == 0)) || ft_isdigit(*tmp)))
			die("Error: nbr_cycles for -dump option must be a valid number!");
		tmp++;
		j++;
	}
	vm->nbr_cycles = ft_atoi(num);
}
