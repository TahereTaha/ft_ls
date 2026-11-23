/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:35:58 by tatahere          #+#    #+#             */
/*   Updated: 2026/11/23 18:28:45 by tatahere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "utils.h"

void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	if (!lst)
		return ;
	t_list	*i = lst;
	while (i->next)
	{
		t_list	*smallest = i;
		t_list	*current = i->next;
		while (current)
		{
			if (cmp(smallest->content, current->content))
				smallest = current;
			current = current->next;
		}
		void	*tmp;
		tmp = i->content;
		i->content = smallest->content;
		smallest->content = tmp;
		i = i->next;
	}
}
