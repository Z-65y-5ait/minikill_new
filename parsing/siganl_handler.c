/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siganl_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:26:42 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 15:29:16 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_ign_handler(void)
{
	struct	sigaction s;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
}

void	sig_int_handler(void)
{
	struct	sigaction s;

	sigemptyset(&s.sa_mask);
	s.sa_flags = 0;
	s.sa_handler = sig_int_handle;
	sigaction(SIGINT, &s, NULL);
}
