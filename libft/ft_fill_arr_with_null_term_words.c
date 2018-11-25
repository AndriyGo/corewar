/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_arr_with_null_term_words.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 17:33:16 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fill_arr_with_null_term_words(char **array, char *s, size_t count)
{
	while (count > 0)
	{
		if ((ft_strlen(s) == 0))
		{
			s += 1;
			continue ;
		}
		if ((*array = ft_strdup(s)) == NULL)
			return (0);
		s = ft_strchr(s, '\0') + 1;
		array++;
		count--;
	}
	return (1);
}
