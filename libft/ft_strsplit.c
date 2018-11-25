/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 17:35:04 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	size_t		count;
	char		*tmp;
	char		**ret;

	if ((s == NULL) || ((tmp = ft_strdup(s)) == NULL))
		return (NULL);
	count = ft_count_and_delim_words(tmp, c);
	if ((ret = (char **)ft_memalloc((count + 1) * sizeof(char *))) == NULL)
		return (NULL);
	if (ft_fill_arr_with_null_term_words(ret, tmp, count) != 1)
		return (NULL);
	*(ret + count) = NULL;
	ft_memdel((void **)&tmp);
	return (ret);
}
