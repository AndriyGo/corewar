/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_printer1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/29 14:08:44 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unicode(uint32_t *str, t_format *flags, int *count)
{
	int			len;
	int			w;
	int			f;

	if (str == NULL)
	{
		print_string((char *)str, flags, count);
		return ;
	}
	len = unicode_str_length(str, flags);
	flags->precision = -1;
	print_left_padding(flags, "", len);
	w = flags->min_width;
	flags->min_width = 0;
	f = 0;
	while ((*str != 0) && (f <= len))
		if ((((f += unicode_length(*str)) <= len) || (w == -1)))
			print_unicode_char(*(str++), flags, count);
	flags->min_width = w;
	print_right_padding(flags, len);
	*count += (w > len) ? (w - len) : 0;
}

void	print_unicode_char(uint32_t c, t_format *flags, int *count)
{
	if (c <= 0x7f)
		print_1b_unicode(c, flags, count);
	else if ((c >= 0x0080) && (c <= 0x07FF))
		print_2b_unicode(c, flags, count);
	else if ((c >= 0x0800) && (c <= 0xFFFF))
		print_3b_unicode(c, flags, count);
	else if ((c >= 0x010000) && (c <= 0x10FFFF))
		print_4b_unicode(c, flags, count);
}

void	print_string(char *str, t_format *flags, int *count)
{
	char	*str2;
	char	*tmp;

	if (str == NULL)
		tmp = ft_strdup_f("(null)");
	else
		tmp = str;
	if ((flags->precision >= 0) && (flags->precision < (int)ft_strlen(tmp)))
	{
		str2 = ft_strsub_f(tmp, 0, flags->precision);
		flags->precision = -1;
		display_string(str2, flags, "", count);
		ft_memdel((void **)&str2);
	}
	else
		display_string(tmp, flags, "", count);
	if (str == NULL)
		ft_memdel((void **)&tmp);
}

void	print_char(char c, t_format *flags, int *count)
{
	flags->precision = -1;
	print_left_padding(flags, "", 1);
	write(1, &c, 1);
	print_right_padding(flags, 1);
	*count += (1 >= flags->min_width) ? 1 : flags->min_width;
}
