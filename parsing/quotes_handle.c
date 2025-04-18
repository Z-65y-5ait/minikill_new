/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:23:31 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 14:45:33 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_words(char *rl, int *i)
{
	char *buff;
	char *temp;
	char quote;

	quote = 0;
	buff = NULL;
    while (rl[*i])
    {
		if (!quote && (rl[*i] == '\'' || rl[*i] == '"'))
		{
			quote = rl[*i];
			(*i)++;
			continue;
		}
        if (quote && rl[*i] == quote)
        {
			quote = 0;
            (*i)++;
            continue;
        }
        if (!quote && ft_strchr(">|< \t$", rl[*i]))
            break;
        temp = ft_strjoin_char(buff, rl[*i]);
        if (!temp)
        {
            free(buff);
            return (NULL);
        }
        free(buff);
        buff = temp;
        (*i)++;
    }
	return (buff);
}
