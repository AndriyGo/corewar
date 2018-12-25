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
	while (n < 66)
	{
		i = 3;
		while (i <= 192)
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
		// fprintf(stderr, "%d\n", tmp->pc);
		mvprintw(x, y, "%02x", vm->mem[tmp->pc]->value);
		if (vm->mem[tmp->pc]->player == NULL)
			attroff(COLOR_PAIR(5));
		else
			attroff(COLOR_PAIR(vm->mem[tmp->pc]->player->idx * (-1) + 5));
		tmp = tmp->next;
	}
}

int				print_players(t_player *pl)
{
	int			j;

	j = 11;
	while (pl)
	{
		mvprintw(j, Y_1 + 3, "Player %d :", pl->idx);
		attron(COLOR_PAIR(-pl->idx));
		mvprintw(j, Y_1 + 15, "%s", pl->name);
		attroff(COLOR_PAIR(-pl->idx));
		mvprintw(j + 1, Y_1 + 6, "Last live : % 21d", pl->last_live);
		mvprintw(j + 2, Y_1 + 6, "Lives in current period : % 7d", pl->lives);
		j += 4;
		pl = pl->next;
	}
	return (j);
}

void			visualization(t_vm *vm)
{
	int			j;

	attron(COLOR_PAIR(12) | A_BOLD);
	mvprintw(4, Y_1 + 3, "Cycles/second limit : %d", 50);
	mvprintw(6, Y_1 + 3, "Total cycle : %d", (vm)->cycle);
	mvprintw(7, Y_1 + 3, "Cycle : %d", (vm)->cycle_);
	mvprintw(9, Y_1 + 3, "Processes : %d", process_count(vm));
	j = print_players(vm->player);
	mvprintw(j, Y_1 + 3, "CYCLE_TO_DIE : %d", vm->cycle_to_die);
	mvprintw(j + 2, Y_1 + 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvprintw(j + 4, Y_1 + 3, "NBR_LIVE : %d", NBR_LIVE);
	mvprintw(j + 6, Y_1 + 3, "MAX_CHECKS : %d", MAX_CHECKS);
	attroff(COLOR_PAIR(12) | A_BOLD);
	draw_map(vm);
	draw_carrys(vm);
	refresh();
}
