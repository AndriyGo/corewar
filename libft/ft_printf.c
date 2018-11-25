/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/25 21:00:58 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

int			simple_print(const char **fmt, int *count)
{
	if (**fmt == '%')
	{
		(*fmt)++;
		return (0);
	}
	else
	{
		write(1, *fmt, 1);
		*count = *count + 1;
	}
	return (1);
}

void		start_work(const char **fmt, t_format *flags, va_list *ap, \
	int *count)
{
	if ((flags->type == 's') && (flags->size == L))
		print_unicode(va_arg(*ap, uint32_t *), flags, count);
	else if (flags->type == 's')
		print_string(va_arg(*ap, char *), flags, count);
	else if ((flags->type == 'c') && (flags->size == L))
		print_unicode_char(va_arg(*ap, uint32_t), flags, count);
	else if (flags->type == 'c')
		print_char(va_arg(*ap, int), flags, count);
	else if (flags->type == 'p')
		print_pointer(va_arg(*ap, void *), flags, count);
	else if (flags->type == 'u')
		cast_and_print_num_u(ap, 10, flags, count);
	else if (flags->type == '%')
	{
		flags->precision = -1;
		print_string("%", flags, count);
	}
	else if ((flags->type == 'd') || (flags->type == 'i'))
		cast_and_print_num(ap, 10, flags, count);
	else if ((flags->type == 'x') || (flags->type == 'X'))
		cast_and_print_num_u(ap, 16, flags, count);
	else if (flags->type == 'o')
		cast_and_print_num_u(ap, 8, flags, count);
	else if (**fmt != 0)
		print_char(*((*fmt)++), flags, count);
}

int			ft_printf(const char *fmt, ...)
{
	va_list		ap;
	t_format	*flags;
	int			count;

	va_start(ap, fmt);
	count = 0;
	while (*fmt)
	{
		if (!simple_print(&fmt, &count))
		{
			flags = read_format(&fmt, &ap);
			optimise_flags(flags);
			start_work(&fmt, flags, &ap, &count);
			ft_memdel((void **)(&flags));
			fmt--;
		}
		fmt++;
	}
	va_end(ap);
	return (count);
}
