/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsemyzhe <jsemyzhe@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:31:09 by jsemyzhe          #+#    #+#             */
/*   Updated: 2018/12/24 14:31:12 by jsemyzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

static void		parse_keys(t_vm *vm)
{
	int key;

	key = getch();
	if (key == 32)
		vm->paused = 1;
	else if (key == 113 && vm->fps > 1)
		vm->fps = (vm->fps - 10 < 1 ? 1 : vm->fps - 10);
	else if (key == 119 && vm->fps > 1)
		vm->fps -= 1;
	else if (key == 101 && vm->fps < 1000)
		vm->fps += 1;
	else if (key == 114 && vm->fps < 1000)
		vm->fps = (vm->fps + 10 > 1000 ? 1000 : vm->fps + 10);
	else if (key == 27)
	{
		endwin();
		exit(0);
	}
	wattron(stdscr, A_BOLD);
	mvprintw(4, Y_1 + 3, "Cycles/second limit : %d   ", vm->fps);
}

static void		pause_(t_vm *vm)
{
	wattron(stdscr, A_BOLD);
	mvprintw(2, Y_1 + 3, "** PAUSED  **");
	while (1)
	{
		vm->paused = 0;
		parse_keys(vm);
		if (vm->paused == 1)
		{
			vm->paused = 0;
			break ;
		}
	}
	mvprintw(2, Y_1 + 3, "** RUNNING **");
	wattroff(stdscr, A_BOLD);
}

void			read_key(t_vm *vm)
{
	parse_keys(vm);
	if (vm->paused == 1)
		pause_(vm);
}

int				print_players(t_player *pl)
{
	int			j;

	j = 11;
	while (pl)
	{
		mvprintw(j, Y_1 + 3, "Player %d :", pl->idx);
		attron(COLOR_PAIR(-pl->idx));
		mvprintw(j, Y_1 + 15, "%.42s", pl->name);
		attroff(COLOR_PAIR(-pl->idx));
		mvprintw(j + 1, Y_1 + 6, "Last live : % 21d   ", pl->last_live);
		mvprintw(j + 2, Y_1 + 6, "Lives in current "
			"period : % 7d   ", pl->lives);
		j += 4;
		pl = pl->next;
	}
	return (j);
}

void			announce_winner(t_vm *vm, int j)
{
	t_player	*winner;

	winner = print_victory(vm, 0);
	attron(A_BOLD);
	mvprintw(j + 8, Y_1 + 3, "The winner is : ");
	attron(COLOR_PAIR(winner->n));
	mvprintw(j + 8, Y_1 + 19, "%.38s", winner->name);
	attroff(COLOR_PAIR(winner->n));
	mvprintw(j + 10, Y_1 + 3, "Press any key to finish");
	refresh();
	while (getch() == -1)
		;
	endwin();
	exit(0);
}
