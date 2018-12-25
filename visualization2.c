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
	else if (key == 27 || key == 113)
	{
		endwin();
		exit(0);
	}
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
