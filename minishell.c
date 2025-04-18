/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 16:07:28 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_token_list(t_token *lst)
{
    t_token *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_parse(t_parse *cmd)
{
    t_parse *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->cmd_name);
        if (tmp->args)
        {
            i = 0;
            while (tmp->args[i])
                free(tmp->args[i++]);
            free(tmp->args);
        }
        while (tmp->file)
        {
            free(tmp->file->name);
            free(tmp->file->type);
            free(tmp->file);
            tmp->file = tmp->file->next;
        }
        free(tmp);
    }
}

t_state_loop ft_state_loop(t_token *token, char *rl)
{
    t_parse *cmd;
    t_error_type state;

    cmd = parse_piped_commands(&token);
    if (!cmd)
        return (CONTINUE);
    state = ft_handle_error(cmd, rl);
    if (state == ERR_UNCLOSED_QUOTES)
        return (free_parse(cmd), printf("minishell: Syntax error: Unclosed quotes\n"), CONTINUE);
    else if (state == ERR_TOO_MANY_ARGS)
        return (free_parse(cmd), printf("minishell: Syntax error: Too many arguments\n"), CONTINUE);
    else if (state == ERR_NUM_ARG)
    {
        printf("exit\n");
        if (cmd->args[1])
            printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
        free_parse(cmd);
        return (BREAK);
    }
    else
    {
        ft_print_list(cmd);
        free_parse(cmd);
        return (CONTINUE);
    }
}

void	minishell_loop()
{
	char        *rl;
	t_parse     *cmd;
	t_token     *token;
	t_state_loop state_loop;

	while(1)
    {
        rl = readline("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37m");
		if (!rl)
		{
			printf("\x1b[32mminishell\x1b[34m-\x1b[31m$ \x1b[37mexit\n");
		    break;
		}
		add_history(rl);
		token = ft_add_cmd(rl);
		if (validate_pipes(token))
		{
			ft_state_loop(token, rl);
            if (state_loop == BREAK)
                break;
		}
		ft_free_token_list(token);
		free(rl);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	sig_int_handler();
	sig_ign_handler();
	if (argc == 1)
		minishell_loop();
    return (0);
}
