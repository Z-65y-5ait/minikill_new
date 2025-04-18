/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:45:36 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:08:17 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins_check(t_parse *par)
{
	if (!par || !par->cmd_name)
		return ;
	if (par->cmd_name && (f_strcmp(par->cmd_name, "echo") == 0)
		|| f_strcmp(par->cmd_name, "cd") == 0
		|| f_strcmp(par->cmd_name, "pwd") == 0
		|| f_strcmp(par->cmd_name, "export") == 0
		|| f_strcmp(par->cmd_name, "unset") == 0
		|| f_strcmp(par->cmd_name, "env") == 0
		|| f_strcmp(par->cmd_name, "exit") == 0)
		par->builtins = 1;
	else
		par->builtins = 0;
}

int count_words_before_pipe(t_token *token)
{
    int count;
	
	count = 0;
    while (token && token->type != T_PIPE)
    {
        if (token->type == T_WORD || token->type == T_VARIABLE)
            count++;
        token = token->next;
    }
    return (count);
}

void	handle_redirection(t_token **check, t_parse **p)
{
	t_token_type	type;

	type = (*check)->type;
	*check = (*check)->next;
	if (!*check)
		return ;
	if (type == T_REDIR_IN)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "REDIR_IN"));
	else if (type == T_REDIR_OUT)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "REDIR_OUT"));
	else if (type == T_APPEND)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "APPEND"));
	else if (type == T_HERDOC)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "HERDOC"));
	*check = (*check)->next;
}
