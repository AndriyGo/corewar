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

void	pause_(t_vm *vm)
{
	int	key;

	key = 0;
	mvprintw(2, Y_1 + 3, "** PAUSED **");
	while (key != 32)
	{
		key = getch();
	}
	vm->paused = 0;
	mvprintw(2, Y_1 + 3, "** RUNNING **");
}

void	read_key(t_vm *vm)
{
	int	key;

	if (vm->paused)
		pause_(vm);
	timeout(1000 / vm->c_per_sec);
	key = getch();
}
