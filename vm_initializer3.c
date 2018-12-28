/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initializer3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:12:46 by agordiyc          #+#    #+#             */
/*   Updated: 2018/12/25 18:14:01 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

void	create_player2(t_vm *vm, char *filename, int idx)
{
	int				fd;
	char			*tmp;
	char			*hex;
	unsigned char	c[1];
	char			*file;

	if ((fd = open(filename, O_RDONLY, 0)) == -1)
		die("Error: Cannot open champion file!");
	if ((file = ft_memalloc(sizeof(char))) == NULL)
		die("Error: Out of memory!");
	while (read(fd, c, 1) > 0)
	{
		tmp = file;
		hex = hex_string(c[0]);
		file = ft_strjoin(file, hex);
		free(hex);
		free(tmp);
	}
	validate_file(file);
	add_player(vm, file, idx);
	free(file);
}
