#include "corewarVM.h"

void	print_usage()
{
	ft_printf("Usage: ./corewar [-dump nbr_cycles] [-v] [[-n number] champion1.cor] ...\n");
	ft_printf("   -dump:\n");
	ft_printf("        after nbr_cycles of executions, memory is dumped on standard output and the game terminates\n");
	ft_printf("   -v:\n");
	ft_printf("        visual mode.\n");
	ft_printf("   -n:\n");
	ft_printf("        specifies custom player number.\n");
	ft_printf("        IMPORTANT: it is your responsibility to ensure that number is valid.\n");
	ft_printf("        E.g. a game cannot be played between 2 players with numbers 1 and 3!\n");
	ft_printf("NOTE: a game must contain between 1 and %d players!\n", MAX_PLAYERS);
	exit(0);
}

int		count_players(t_vm *vm)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = vm->player;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	if (i > MAX_PLAYERS)
		die("Error: Max number of players exceeded!");
	return (i);
}

void	sort_players(t_vm *vm)
{
	int			c;
	t_player	*tmp;
	t_player	*tmp2;
	int			i;

	c = count_players(vm);
	tmp = vm->player;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		if (tmp->idx > c)
			die("Error: Player index cannot exceed players count!");
		if ((tmp->idx > 0) && (tmp->idx != i))
		{
			i = 1;
			tmp2 = vm->player;
			while (i++ < tmp->idx)
				tmp2 = tmp2->next;
			tmp->next = tmp2->next;
			tmp2->next = tmp;
			tmp = vm->player;
			i = 0;
		}
		else
			tmp = tmp->next;
	}
}

void	game_move(t_vm *vm)
{
	t_process	*tmp;

	if (vm->cycle == vm->nbr_cycles)
		dump(vm);
	vm->cycle += 1;
	tmp = vm->process;
	while (tmp)
	{
		tik_process(tmp);
		tmp = tmp->next;
	}
	ft_printf("SHOW MUST GO ON!\n");
}

void	start_game(t_vm *vm)
{
	int 		i;
	int			c;
	int 		l;
	t_player	*tmp;

	if (vm->player == NULL)
		print_usage();
	sort_players(vm);
	c = count_players(vm);
	l = MEM_SIZE / c;
	tmp = vm->player;
	i = 0;
	while (tmp != NULL)
	{
		c = -1;
		while (tmp->instructions[++c])
		{
			vm->mem[i + (c / 2) + (c % 2)]->value = hex_to_int(tmp->instructions[c]) * 16 + hex_to_int(tmp->instructions[c+1]);
			c++;
		}
		add_process(vm, i);
		i += l;
		tmp = tmp->next;
	}
	game_move(vm);
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int		i;
	int		idx;

	create_vm(&vm);
	i = 1;
	idx = -1;
	while (i < argc)
	{
		if (idx >0)
		{
			create_player(vm, argv[i], idx);
			idx = -1;
		}
		else if (ft_strcmp(argv[i], "-v") == 0)
			vm->visual_mode = 1;
		else if (ft_strcmp(argv[i], "-dump") == 0)
			read_dump(vm, ++i, argc, argv);
		else if (ft_strcmp(argv[i], "-n") == 0)
			idx = player_index(++i, argc, argv);
		else
			create_player(vm, argv[i], -1);
		i++;
	}
	start_game(vm);
}