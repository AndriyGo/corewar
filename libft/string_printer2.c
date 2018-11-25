/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_printer2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:28:24 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/25 20:56:27 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		unicode_length(uint32_t c)
{
	if (c <= 0x7f)
		return (1);
	else if ((c >= 0x0080) && (c <= 0x07FF))
		return (MB_CUR_MAX >= 2) ? 2 : (c < 256);
	else if ((c >= 0x0800) && (c <= 0xFFFF))
		return (MB_CUR_MAX >= 3) ? 3 : 0;
	else if ((c >= 0x010000) && (c <= 0x10FFFF))
		return (MB_CUR_MAX >= 4) ? 4 : 0;
	return (0);
}

int		unicode_str_length(uint32_t *str, t_format *flags)
{
	int			len;

	len = 0;
	while ((*str != 0) && ((flags->precision == -1) || \
		(flags->precision >= unicode_length(*str))))
	{
		len += unicode_length(*str);
		if (flags->precision != -1)
			flags->precision -= unicode_length(*str);
		str++;
	}
	return (len);
}

char	*ft_strdup_f(const char *s)
{
	char	*ret;

	if (((ret = ft_strdup(s)) == NULL) && (s != NULL))
		exit(EXIT_FAILURE);
	return (ret);
}

char	*ft_strsub_f(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (((ret = ft_strsub(s, start, len)) == NULL) && (s != NULL))
		exit(EXIT_FAILURE);
	return (ret);
}

char	*ft_strjoin_f(char const *s1, char const *s2)
{
	char	*ret;

	if (((ret = ft_strjoin(s1, s2)) == NULL) && (s1 != NULL) && \
		(s2 != NULL))
		exit(EXIT_FAILURE);
	return (ret);
}
