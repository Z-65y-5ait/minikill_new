/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 03:10:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:08:52 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (lst && new)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			head = ft_lstlast((*lst));
			head->next = new;
		}
	}
}

void ft_lstadd_back_files(t_parse **p, t_files *new)
{
	t_files *tmp;
	
    if (!new)
        return;
    if (!(*p)->file)
    {
        (*p)->file = new;
        return;
    }
    tmp = (*p)->file;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token *tmp;

    if (!new)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	if (lst && del)
	{
		while ((*lst) != NULL)
		{
			head = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			(*lst) = head;
		}
		*lst = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
