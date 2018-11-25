/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_and_delim_words.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 17:35:16 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_and_delim_words(char *s, char delim)
{
	char	*tmp;
	size_t	count;

	count = 0;
	while ((tmp = ft_strchr(s, delim)) != NULL)
	{
		if ((tmp - s > 0) && (*(tmp - 1) != '\0'))
			count++;
		*tmp = '\0';
		s = ++tmp;
	}
	if (*s != '\0')
		count++;
	return (count);
}
