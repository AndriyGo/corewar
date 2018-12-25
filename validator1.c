/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyerin <iyerin@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:35:19 by iyerin            #+#    #+#             */
/*   Updated: 2018/12/25 19:35:23 by iyerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewarvm.h"

int				binary_chars_valid(char *file)
{
	int	ok;

	while (*file)
	{
		ok = 0;
		if ((*file >= '0') && (*file <= '9'))
			ok = 1;
		if ((*file >= 'A') && (*file <= 'F'))
			ok = 1;
		if ((*file >= 'a') && (*file <= 'f'))
			ok = 1;
		if (ok == 0)
			return (0);
		file++;
	}
	return (1);
}

int				magic_header_ok(char *file)
{
	int	header;
	int	i;

	header = 0;
	i = 0;
	while (i < hex_len(COREWAR_EXEC_MAGIC))
	{
		header = header * 16 + hex_to_int(*file);
		file++;
		header = header * 16 + hex_to_int(*file);
		file++;
		i++;
	}
	return (header == COREWAR_EXEC_MAGIC);
}

int				null_valid(char *file)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		if (*(file++) != '0')
			return (0);
	}
	return (1);
}

unsigned long	bot_length(char *file)
{
	unsigned long	header;
	int				i;

	header = 0;
	i = 0;
	while (i < 4)
	{
		header = header * 16 + hex_to_int(*file);
		file++;
		header = header * 16 + hex_to_int(*file);
		file++;
		i++;
	}
	return (header);
}

void			validate_file(char *file)
{
	if (ft_strlen(file) <= (size_t)((PROG_NAME_LENGTH + COMMENT_LENGTH
		+ 12 + hex_len(COREWAR_EXEC_MAGIC)) * 2))
		die("Error: Champion binary file too small.");
	if (binary_chars_valid(file) == 0)
		die("Error: Champion binary contains non-hex values.");
	if (magic_header_ok(file) == 0)
		die("Error: Champion binary starts with wrong magic header.");
	if (null_valid(file + (size_t)(hex_len(COREWAR_EXEC_MAGIC)
		+ PROG_NAME_LENGTH) * 2) == 0)
		die("Error: Champion binary misses NULL after bot name.");
	if (null_valid(file + (size_t)((PROG_NAME_LENGTH + COMMENT_LENGTH
		+ 8 + hex_len(COREWAR_EXEC_MAGIC)) * 2)) == 0)
		die("Error: Champion binary misses NULL after comment.");
	if (bot_length(file + (size_t)((PROG_NAME_LENGTH + 4 + hex_len(
		COREWAR_EXEC_MAGIC)) * 2)) > CHAMP_MAX_SIZE)
		die("Error: Declared champion size greater than maximum allowed size.");
	if (bot_length(file + (size_t)((PROG_NAME_LENGTH + 4 + hex_len(
		COREWAR_EXEC_MAGIC)) * 2)) * 2 != ft_strlen(file) - (size_t)((
		PROG_NAME_LENGTH + COMMENT_LENGTH + 12 + hex_len(COREWAR_EXEC_MAGIC))
		* 2))
		die("Error: Declared champion size does not match its actual size.");
}
