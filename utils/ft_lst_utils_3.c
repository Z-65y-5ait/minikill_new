/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:51:14 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:08:56 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_token(t_token *token)
{
	int		count;
	t_token	*head;

	head = token;
	count = 1;
	if (!token)
		return (0);
	while (head != NULL && head->type == T_WORD)
	{
		count++;
		head = head->next;
	}
	return (count);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}
