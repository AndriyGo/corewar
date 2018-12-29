/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemyzhe <jsemyzhe@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:31:28 by jsemyzhe          #+#    #+#             */
/*   Updated: 2018/12/24 14:31:29 by jsemyzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

static void		ft_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_color(COLOR_MAGENTA, 1000, 1000, 1000);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(16, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(17, COLOR_MAGENTA, COLOR_RED);
	init_pair(18, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(19, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(11, COLOR_WHITE, COLOR_WHITE);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
}

void			initiate_visualization(void)
{
	int			i;

	initscr();
	keypad(stdscr, true);
	timeout(0);
	curs_set(false);
	cbreak();
	noecho();
	ft_colors();
	attron(COLOR_PAIR(11));
	i = 67;
	while (i >= 0)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, Y_1 + Y_2, "*");
		mvprintw(i, Y_1, "*");
		i--;
	}
	i = 254;
	while (--i >= 0)
	{
		mvprintw(0, i, "*");
		mvprintw(X_1, i, "*");
	}
	attroff(COLOR_PAIR(11));
}

static void		draw_map(t_vm *vm)
{
	int			i;
	int			n;
	int			j;

	j = 0;
	n = 2;
	while (n < MEM_SIZE / 64 + 3 && (n - 2) * 64 != MEM_SIZE)
	{
		i = 3;
		while (i <= 192 && ((n - 2) * 64 + (i / 3)) <= MEM_SIZE)
		{
			if (vm->mem[j]->player != NULL)
				attron(COLOR_PAIR(vm->mem[j]->player->idx * (-1)));
			if (vm->mem[j]->last_update > 0 && (vm->mem[j]->last_update--))
				attron(A_BOLD);
			mvprintw(n, i, "%02x", vm->mem[j]->value);
			if (vm->mem[j]->player != NULL)
				attroff(COLOR_PAIR(vm->mem[j]->player->idx * (-1)) | A_BOLD);
			i += 3;
			j++;
		}
		n++;
	}
}

static void		draw_carrys(t_vm *vm)
{
	t_process	*tmp;
	int			x;
	int			y;

	tmp = vm->process;
	while (tmp)
	{
		if (vm->mem[tmp->pc]->player == NULL)
			attron(COLOR_PAIR(5) | A_BOLD);
		else
			attron(COLOR_PAIR(vm->mem[tmp->pc]->player->idx * (-1) + 5));
		x = tmp->pc / 64 + 2;
		y = tmp->pc % 64 * 3 + 3;
		mvprintw(x, y, "%02x", vm->mem[tmp->pc]->value);
		if (vm->mem[tmp->pc]->player == NULL)
			attroff(COLOR_PAIR(5));
		else
			attroff(COLOR_PAIR(vm->mem[tmp->pc]->player->idx * (-1) + 5));
		tmp = tmp->next;
	}
}

void			visualization(t_vm *vm)
{
	int			j;

	if (vm->visual_mode == 0)
		return ;
	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw(4, Y_1 + 3, "Cycles/second limit : %d   ", vm->fps);
	mvprintw(6, Y_1 + 3, "Total cycle : %d   ", (vm)->cycle);
	mvprintw(7, Y_1 + 3, "Cycle : %d   ", (vm)->cycle_);
	mvprintw(9, Y_1 + 3, "Processes : %d     ", process_count(vm));
	j = print_players(vm->player);
	mvprintw(j, Y_1 + 3, "CYCLE_TO_DIE : %d   ", vm->cycle_to_die);
	mvprintw(j + 2, Y_1 + 3, "CYCLE_DELTA : %d   ", CYCLE_DELTA);
	mvprintw(j + 4, Y_1 + 3, "NBR_LIVE : %d   ", NBR_LIVE);
	mvprintw(j + 6, Y_1 + 3, "MAX_CHECKS : %d   ", MAX_CHECKS);
	attroff(COLOR_PAIR(12) | A_BOLD);
	draw_map(vm);
	draw_carrys(vm);
	if (vm->game_on == 0)
		announce_winner(vm, j);
	refresh();
	while (clock() < vm->next_cycle_time)
		read_key(vm);
	vm->next_cycle_time = clock() + 1000000 / vm->fps;
	read_key(vm);
}
