/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

t_player	*print_victory(t_vm *vm, int print)
{
	t_player	*tmp;

	if (vm->winner == NULL)
	{
		tmp = vm->player;
		while (tmp)
		{
			vm->winner = tmp;
			tmp = tmp->next;
		}
	}
	if (print)
		ft_printf("Contestant %d, \"%s\", "
			"has won !\n", vm->winner->n, vm->winner->name);
	return (vm->winner);
}

void		game_move(t_vm *vm)
{
	t_process	*tmp;

	dump(vm);
	visualization(vm);
	vm->cycle += 1;
	vm->cycle_ += 1;
	tmp = vm->process;
	while (tmp && (vm->cycle_to_die > 0))
		tik_process(&tmp);
	if ((vm->cycle_ == vm->cycle_to_die) || (vm->cycle_to_die < 0))
	{
		remove_dead_p(vm);
		vm->checks -= 1;
		decrease_cycle_to_die(vm);
		vm->cycle_ = 0;
		if (vm->game_on == 0)
		{
			if (vm->visual_mode == 1)
				visualization(vm);
			else
				print_victory(vm, 1);
			exit(1);
		}
	}
}

void		start_game2(t_vm *vm, int l, int i)
{
	int			c;
	t_player	*tmp;

	tmp = vm->player;
	i = 0;
	while (tmp != NULL)
	{
		c = -1;
		while (tmp->instructions[++c])
		{
			vm->mem[i + (c / 2) + (c % 2)]->value = hex_to_int(
			tmp->instructions[c]) * 16 + hex_to_int(tmp->instructions[c + 1]);
			vm->mem[i + (c / 2) + (c % 2)]->player = tmp;
			c++;
		}
		add_process(vm, i, tmp);
		i += l;
		tmp = tmp->next;
	}
	if (vm->visual_mode == 1)
		initiate_visualization();
	else
		print_intro(vm);
	while (vm->game_on == 1)
		game_move(vm);
}

void		start_game1(t_vm *vm)
{
	int	l;

	vm->log = vm->log && (vm->visual_mode == 0);
	vm->next_cycle_time = clock() + 1000000 / vm->fps;
	if (vm->player == NULL)
		print_usage();
	sort_players(vm);
	l = MEM_SIZE / count_players(vm);
	start_game2(vm, l, 0);
}

int			main(int argc, char **argv)
{
	t_vm	*vm;
	int		i;
	int		idx;

	create_vm(&vm);
	i = 1;
	idx = -1;
	while (i < argc)
	{
		if (idx > 0)
			create_player(vm, argv[i], &idx);
		else if (ft_strcmp(argv[i], "-v") == 0)
			vm->visual_mode = 1;
		else if (ft_strcmp(argv[i], "-l") == 0)
			vm->log = 1;
		else if (ft_strcmp(argv[i], "-dump") == 0)
			read_dump(vm, ++i, argc, argv);
		else if (ft_strcmp(argv[i], "-n") == 0)
			idx = player_index(++i, argc, argv);
		else
			create_player2(vm, argv[i], -1);
		i++;
	}
	start_game1(vm);
}
