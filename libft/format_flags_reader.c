/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_flags_reader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/25 20:42:04 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		read_size(const char **size, t_format *ret)
{
	if (**size == 'h')
	{
		if (ret->size == H)
			ret->size = HH;
		else if (ret->size < H)
			ret->size = H;
	}
	else if (**size == 'l')
	{
		if (ret->size == L)
			ret->size = LL;
		else if (ret->size < L)
			ret->size = L;
	}
	else if (**size == 'j')
	{
		if (ret->size < J)
			ret->size = J;
	}
	else if (ret->size < Z)
		ret->size = Z;
}

int			read_number(const char **fmt)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**fmt))
		ret = ret * 10 + (*((*fmt)++) - '0');
	(*fmt)--;
	return (ret);
}

t_format	*init_flags(void)
{
	t_format	*ret;

	if ((ret = ft_memalloc(sizeof(t_format))) == NULL)
		exit(EXIT_FAILURE);
	ret->size = 0;
	ret->type = -1;
	ret->min_width = 0;
	ret->precision = -1;
	ret->alternate = 0;
	ret->zero_pad = 0;
	ret->neg_width = 0;
	ret->space = 0;
	ret->sign_always = 0;
	return (ret);
}

int			read_format_specifier(const char *fmt, t_format *flags)
{
	if ((*fmt == 's') || (*fmt == 'S') || (*fmt == 'p') || (*fmt == 'd') \
		|| (*fmt == 'D') || (*fmt == 'i') || (*fmt == 'o') || (*fmt == 'O') \
		|| (*fmt == 'u') || (*fmt == 'U') || (*fmt == 'x') || (*fmt == 'X') \
		|| (*fmt == 'c') || (*fmt == 'C') || (*fmt == '%'))
	{
		flags->type = *fmt;
		return (1);
	}
	return (0);
}

t_format	*read_format(const char **fmt, va_list *ap)
{
	t_format	*ret;

	ret = init_flags();
	while ((**fmt) && (ret->type == -1))
	{
		if (read_format2(fmt, ret))
		{
		}
		else if (**fmt == '.')
		{
			(*fmt)++;
			if (**fmt == '*')
				ret->precision = va_arg(*ap, int);
			else
				ret->precision = read_number(fmt);
		}
		else if (**fmt == '*')
			ret->min_width = va_arg(*ap, int);
		else if (read_format_specifier(*fmt, ret) == 0)
			break ;
		(*fmt)++;
	}
	return (ret);
}
