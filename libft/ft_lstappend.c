/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agordiyc <agordiyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:03:20 by agordiyc          #+#    #+#             */
/*   Updated: 2018/10/29 14:03:36 by agordiyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list *alst, t_list *new)
{
	t_list	*tmp;

	if ((new == NULL) || (alst == NULL))
		return ;
	tmp = alst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
