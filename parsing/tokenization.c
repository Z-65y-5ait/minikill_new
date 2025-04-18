/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:43:49 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 14:52:33 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_handle_word(char *rl, int *i, t_token **lst, t_variable *var)
{
	char *buff;
	char *var_str;

	buff = ft_handle_words(rl, i);
	if (buff)
	{
		ft_lstadd_back_token(lst, ft_token_new(T_WORD, buff));
		free(buff);
	}
}

void ft_handle_redir_in(char *rl, int *i, t_token **lst)
{
	if(rl[(*i) + 1] == '<')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_HERDOC, ft_strdup("<<")));
		(*i) += 2;
	}
	else if (rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, ft_strdup("<>")));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_IN, ft_strdup("<")));
		(*i)++;
	}
}

void ft_handle_redir_out(char *rl, int *i, t_token **lst)
{
	if (rl[(*i) + 1] == '|')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ft_strdup(">|")));
		(*i) += 2;
	}
	else if(rl[(*i) + 1] == '>')
	{
		ft_lstadd_back_token(lst, ft_token_new(T_APPEND, ft_strdup(">>")));
		(*i) += 2;
	}
	else
	{
		ft_lstadd_back_token(lst, ft_token_new(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}

void ft_handle_variable(char *rl, int *i, t_token **lst, t_variable *var)
{
	char *buff;
	char *var_str;

	(*i)++;
	buff = ft_handle_words(rl, i);
	if (buff)
	{
		var_str = ft_strjoin("$", buff);
		ft_lstadd_back_token(lst, ft_token_new(T_VARIABLE, var_str));
		free(var_str);
		free(buff);
		buff = NULL;
	}
}

void process_char(char *rl, int *i, t_token **lst, t_variable *var)
{
	if (!ft_strchr(">|<$", rl[(*i)]))
		ft_handle_word(rl, i, lst, var);
	else if (rl[(*i)] == '<')
		ft_handle_redir_in(rl, i, lst);
	else if (rl[(*i)] == '>')
		ft_handle_redir_out(rl, i, lst);
	else if (rl[(*i)] == '$')
		ft_handle_variable(rl, i, lst, var);
	else if (rl[(*i)] == '|')
	{
		(*i)++;
		ft_lstadd_back_token(lst, ft_token_new(T_PIPE, ft_strdup("|")));
	}
	else
		(*i)++;
}
