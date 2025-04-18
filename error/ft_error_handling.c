/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:12:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:08:38 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_error_type	ft_handle_error(t_parse *cmd, char *rl)
{
	int 			val;
	t_parse 		*tmp;
	int				state_arg;
	t_error_type	state_empty;
	t_quotes_state	state_quotes;

	state_quotes = ft_handle_quotes(rl);
	state_arg = ft_handle_arg(cmd);
	tmp = cmd;
	val = 1;
	// while (tmp && val)
	// {
	//     if (!ft_handle_arg(tmp))
	//         val = 0;
	//     tmp = tmp->next;
	// }
	if (state_arg == -1)
		return (ERR_NUM_ARG);
	if (state_quotes != NONE)
		return (ERR_UNCLOSED_QUOTES);
	if (!val || !state_arg)
		return (ERR_TOO_MANY_ARGS);
	return (ERR_NONE);
}

// t_error_type validate_pipe_syntax(char *input)
// {
//     char *trimmed;
	
// 	trimmed = ft_strtrim(input, " \t\n\r");
//     if (trimmed[0] == '|' || trimmed[ft_strlen(trimmed) - 1] == '|')
// 	{
//         free(trimmed);
//         return (ERR_EMPTY_SYNTAX);
//     }
//     free(trimmed);
//     return (ERR_NONE);
// }

// t_parse *ft_parse_pipe_syntax(t_token **token)
// {
// 	int 	i;
//     t_parse *cmd;
//     char    *input;
// 	char 	*trimmed;
//     char    **tokens;

// 	input = (*token)->value;
//     tokens = ft_split(input, '|');
//     if (!tokens)
//         return (NULL);
// 	i = 0;
//     while (tokens[i])
// 	{
//         trimmed = ft_strtrim(tokens[i++], " \t\n\r");
//         if (trimmed[0] == '\0')
// 		{
//             printf("minishell: syntax error near unexpected token `|'\n");
//             return (free(trimmed), free_split(tokens), NULL);
//         }
//         free(trimmed);
//     }
//     cmd = ft_parse_pipe(token);
//     free_split(tokens);
//     return (cmd);
// }
