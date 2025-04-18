/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_handle_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:44:40 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:08:35 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quotes_state	ft_handle_quotes(char *rl)
{
	int i;
	t_quotes_state	state;

	i = 0;
	state = NONE;
	while (rl[i])
	{
		if (rl[i] == '\\' && state != S_QUOTES)
		{
		    i++;
		    continue;
  		}
	  	if (state == NONE) 
		{
	    	if (rl[i] == '\'')
				state = S_QUOTES;
	    	else if (rl[i] == '"')
				state = D_QUOTES;
	  	}
		else if ((state == S_QUOTES && rl[i] == '\'') || (state == D_QUOTES && rl[i] == '"'))
	    	state = NONE;
		i++;
	}
	return (state);
}

int	ft_handle_arg(t_parse *cmd)
{
	int count;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	if (count > 100)
		return (0);
	if (cmd->builtins == 1)
	{
		if (f_strcmp(cmd->cmd_name, "cd") == 0)
		{
			if (count > 2)
				return (0);
		}
		else if (f_strcmp(cmd->cmd_name, "env") == 0)
		{
			if (count > 1)
				return (0);
		}
		else if (f_strcmp(cmd->cmd_name, "exit") == 0)
		{
			if (is_numeric(cmd->args[1]) == 0)
				return (-1);
			else if (count > 2)
				return (0);
		}
	}	
	return (1);
}

// t_error_type	ft_handle_pipe(t_parse *cmd)
// {
// 	t_parse *tmp;

// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		if(tmp->cmd_name == NULL || tmp->cmd_name[0] == '\0')
// 			return (ERR_PIPE_SYNTAX);
// 		tmp = tmp->next;
// 	}
// 	return (ERR_NONE);
// }
