/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_any.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 15:46:32 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list_2(t_token *cmd)
{
	t_token *tmp;
	
	tmp = cmd;
	while (tmp)
    {
        if (tmp->value)
            printf("%s -- %d\n", tmp->value, tmp->type);
        else
            printf("(null) -- %d\n", tmp->type);
        tmp = tmp->next;
    }
}

void ft_print_list(t_parse *cmd)
{
    int i;
    t_parse *tmp;
	int node_count;
	t_files *file_tmp;
    
    tmp = cmd;
	node_count = 0;
    while (tmp)
    {
		node_count++;
        printf("Node %d: ", node_count);
        i = 0;
        if (tmp->cmd_name)
            printf("%s -- ", tmp->cmd_name);
        else
            printf("(no command) -- ");
        if (tmp->args) 
        {
            while (tmp->args[i])
            {
                printf("%s ", tmp->args[i]);
                i++;
            }
        }
		else
            printf("(no args) -- ");
		file_tmp = tmp->file;
		while (file_tmp)
		{
        	printf("-- %s -- %s", file_tmp->name, file_tmp->type);
			file_tmp = file_tmp->next;
		}
		printf("-- %d\n", tmp->builtins);
        tmp = tmp->next;
    }
}
