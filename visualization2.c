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

#include "corewarVM.h"

void	pause_()
{
	int	key;

	key = 0;
	while(key != 32)
	{
		key = getch();
	}
}

void	read_key(t_vm *vm)
{
	int	key;

	timeout(1000 / vm->c_per_sec);
	key = getch();
	if (key == 32)
		pause_();
}