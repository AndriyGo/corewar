/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 17:46:06 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace_trim(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n'))
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	length;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	start = 0;
	tmp = (char *)s;
	while (ft_iswhitespace_trim(*tmp))
	{
		tmp++;
		start++;
	}
	length = ft_strlen(s);
	if (length == start)
		return (ft_strdup(""));
	tmp = (char *)s + length - 1;
	length -= start;
	while (ft_iswhitespace_trim(*tmp))
	{
		tmp--;
		length--;
	}
	return (ft_strsub(s, start, length));
}
