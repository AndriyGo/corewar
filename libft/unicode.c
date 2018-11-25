/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/25 16:23:03 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_1b_unicode(uint32_t c, t_format *flags, int *count)
{
	flags->precision = -1;
	print_left_padding(flags, "", 1);
	write(1, &c, 1);
	print_right_padding(flags, 1);
	*count += (1 >= flags->min_width) ? 1 : flags->min_width;
}

void	print_2b_unicode(uint32_t c, t_format *flags, int *count)
{
	int	p;

	if (MB_CUR_MAX >= 2)
		*count += (2 >= flags->min_width) ? 2 : flags->min_width;
	else if (c < 256)
		*count += (1 >= flags->min_width) ? 1 : flags->min_width;
	else
		*count += (0 >= flags->min_width) ? 0 : flags->min_width;
	print_left_padding(flags, "", (MB_CUR_MAX >= 2) ? 2 : (c < 256));
	if (MB_CUR_MAX >= 2)
	{
		p = 0 | 0xC0;
		p = p | ((c & 0x7C0) >> 6);
		write(1, &p, 1);
		p = 0 | 0x80;
		p = p | (c & 0x3F);
		write(1, &p, 1);
	}
	else if (c < 256)
		write(1, &c, 1);
	print_right_padding(flags, (MB_CUR_MAX >= 2) ? 2 : (c < 256));
}

void	print_3b_unicode(uint32_t c, t_format *flags, int *count)
{
	int p;

	print_left_padding(flags, "", (MB_CUR_MAX >= 3) ? 3 : 0);
	if (MB_CUR_MAX >= 3)
	{
		p = 0 | 0xE0;
		p = p | ((c & 0xF000) >> 12);
		write(1, &p, 1);
		p = 0 | 0x80;
		p = p | ((c & 0xFC0) >> 6);
		write(1, &p, 1);
		p = 0 | 0x80;
		p = p | (c & 0x3F);
		write(1, &p, 1);
	}
	print_right_padding(flags, (MB_CUR_MAX >= 3) ? 3 : 0);
	if (MB_CUR_MAX >= 3)
		*count += (3 >= flags->min_width) ? 3 : flags->min_width;
	else
		*count += (0 >= flags->min_width) ? 0 : flags->min_width;
}

void	print_4b_unicode(uint32_t c, t_format *flags, int *count)
{
	int p;

	print_left_padding(flags, "", (MB_CUR_MAX >= 4) ? 4 : 0);
	if (MB_CUR_MAX >= 4)
	{
		p = (0 | 0x1E) | ((c & 0x1C0000) >> 18);
		write(1, &p, 1);
		if (MB_CUR_MAX == 1)
			return ;
		p = (0 | 0x80) | ((c & 0x3F000) >> 12);
		write(1, &p, 1);
		if (MB_CUR_MAX == 2)
			return ;
		p = (0 | 0x80) | ((c & 0xFC0) >> 6);
		write(1, &p, 1);
		if (MB_CUR_MAX == 3)
			return ;
		p = (0 | 0x80) | (c & 0x3F);
		write(1, &p, 1);
	}
	print_right_padding(flags, (MB_CUR_MAX >= 4) ? 4 : 0);
	if (MB_CUR_MAX >= 4)
		*count += (4 >= flags->min_width) ? 4 : flags->min_width;
	else
		*count += (0 >= flags->min_width) ? 0 : flags->min_width;
}
