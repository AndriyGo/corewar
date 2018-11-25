/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:48:46 by agordiyc          #+#    #+#             */
/*   Updated: 2017/12/10 15:51:25 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*ret;

	if (lst == NULL)
		return (NULL);
	ret = ft_lstnew(lst->content, lst->content_size);
	return (ret);
}
