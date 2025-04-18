/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:12:15 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 14:45:06 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *ft_add_cmd(char *rl)
{
	int			i;
	char		*buff;
	char		*var_str;
    t_token		*lst;
	t_variable  var;

	i = 0;
	lst = NULL;
	buff = NULL;
    while(rl[i])
	{
		while (rl[i] == ' ' || rl[i] == '\t')
            i++;
		if(!rl[i])
			break;
		process_char(rl, &i, &lst, &var);
	}
    free(buff);
	
	return (lst);
}

t_parse	*ft_parsing(t_token **token)
{
	int 	i;
	char	**arg;
	t_parse *parse;

	parse = ft_parse_new();
	if (!parse)
		return (NULL);
	arg = ft_check_parse(token, &parse, &i);
	if (!arg)
	{
		free(parse);
        return (NULL);   
	}
	parse->args = arg;
	if (i > 0)
		parse->cmd_name = ft_strdup(arg[0]);
	else
        parse->cmd_name = NULL;
	ft_builtins_check(parse);
	return (parse);
}

char	**ft_check_parse(t_token **check, t_parse **p, int *i)
{
	int		size;
	char	**arg;

	size = count_words_before_pipe(*check) + 1;
	arg = (char **)malloc(sizeof(char *) * size);
	if (!arg)
		return (NULL);
	*i = 0;
	while ((*check) && ((*check)->type != T_PIPE))
	{
		if ((*check)->type == T_REDIR_IN || (*check)->type == T_REDIR_OUT
			|| (*check)->type == T_APPEND || (*check)->type == T_HERDOC)
			handle_redirection(check, p);
		else if ((*check)->type == T_WORD || (*check)->type == T_VARIABLE)
		{
			arg[(*i)++] = ft_strdup((*check)->value);
			(*check) = (*check)->next;
		}
		else
			(*check) = (*check)->next;
	}
	arg[*i] = NULL;
	return (arg);
}

t_parse *parse_piped_commands(t_token **token_p)
{
    t_parse *cmd;
	t_token *token;

	cmd = ft_parsing(token_p);
    if (!cmd)
        return (NULL);
    token = *token_p;
    if (token && token->type == T_PIPE)
    {
        *token_p = token->next;
        cmd->next = parse_piped_commands(token_p);
        if (!cmd->next && *token_p)
            return (NULL);
	}
    return (cmd);
}

int validate_pipes(t_token *token)
{
    int expect_command;
	t_token *next_token;

	expect_command = 1;
    while (token)
    {
		if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT || token->type == T_APPEND)
		{
			next_token = token->next;
			if (!next_token)
				return (printf("minishell: syntax error near unexpected token 'newline'\n"), 0);
			else if (next_token->type == T_PIPE)
                return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
			else if (next_token->type == T_REDIR_IN || next_token->type == T_REDIR_OUT || next_token->type == T_APPEND)
				return (printf("minishell: syntax error near unexpected token '%s'\n", next_token->value), 0);
		}
        else if (token->type == T_PIPE)
        {
            if (expect_command)
                return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
            expect_command = 1;
        }
        else
            expect_command = 0;
        token = token->next;
    }
    // if (expect_command)
    //     return (printf("minishell: syntax error: unexpected end of file\n"), 0);
    return (1);
}
