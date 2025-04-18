/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:18:57 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:10:45 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_new(t_token_type type, void *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (content)
        new->value = ft_strdup(content);
    else
        new->value = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_files	*ft_files_new(char *name, char *type)
{
	t_files *file;

	file = (t_files *)malloc(sizeof(t_files));
	if (!file)
		return (NULL);
	file->name = ft_strdup(name);
	file->type = ft_strdup(type);
	file->next = NULL;
	return (file);
}

t_parse	*ft_parse_new(void)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->cmd_name = NULL;
	new->args = NULL;
	new->file = NULL;
	new->builtins = 0;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*head;

	head = lst;
	count = 1;
	if (!lst)
		return (0);
	while (head->next != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}
