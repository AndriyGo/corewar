/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:11:42 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/29 14:08:21 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

# define HH	1
# define H	2
# define L	3
# define LL	4
# define J	5
# define Z	6

typedef struct	s_format
{
	int		alternate;
	int		zero_pad;
	int		neg_width;
	int		space;
	int		sign_always;
	int		size;
	int		min_width;
	int		precision;
	char	type;
}				t_format;

void			optimise_flags(t_format *flags);
t_format		*read_format(const char **fmt, va_list *ap);
void			print_string(char *str, t_format *flags, int *count);
void			display_string(char *str, t_format *flags, char *prefix, \
				int *count);
void			print_char(char c, t_format *flags, int *count);
char			*num_to_base(intmax_t num, int base, t_format *flags);
char			*num_to_base_u(uintmax_t num, int base, t_format *flags);
void			print_pointer(void *p, t_format *flags, int *count);
void			print_number(intmax_t num, int base, t_format *flags, \
				int *count);
int				compare(char c, char compare);
void			cast_and_print_num(va_list *ap, int base, t_format *flags, \
				int *count);
void			cast_and_print_num_u(va_list *ap, int base, t_format *flags, \
				int *count);
void			capitalize(char *s);
void			print_left_padding(t_format *flags, char *prefix, int len);
void			print_right_padding(t_format *flags, int len);
void			print_unicode_char(uint32_t c, t_format *flags, int *count);
void			print_1b_unicode(uint32_t c, t_format *flags, int *count);
void			print_2b_unicode(uint32_t c, t_format *flags, int *count);
void			print_3b_unicode(uint32_t c, t_format *flags, int *count);
void			print_4b_unicode(uint32_t c, t_format *flags, int *count);
void			print_unicode(uint32_t *str, t_format *flags, int *count);
int				ft_printf(const char *fmt, ...);
int				unicode_str_length(uint32_t *str, t_format *flags);
int				read_format2(const char **c, t_format *ret);
int				read_number(const char **fmt);
void			read_size(const char **size, t_format *ret);
int				unicode_length(uint32_t c);
char			*ft_strdup_f(const char *s);
char			*ft_strsub_f(char const *s, unsigned int start, size_t len);
char			*ft_strjoin_f(char const *s1, char const *s2);

#endif
