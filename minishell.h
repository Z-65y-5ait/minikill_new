/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 15:38:45 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

typedef struct s_process
{
	int saved_fd;
	int pipe[2];
	int cmd_idx;
	char *path;
	char **env;
	struct s_parse	*exec_cmd;
}	t_process;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef enum e_token
{
		T_WORD,
		T_PIPE,
		T_REDIR_IN,
		T_REDIR_OUT,
		T_APPEND,
		T_HERDOC,
		T_SIGN,
		T_VARIABLE,
		T_SQUOTE,
		T_DQUOTE,
}	t_token_type;

typedef enum e_quotes
{
		NONE,
		S_QUOTES,
		D_QUOTES,
}	t_quotes_state;

typedef enum e_loop
{
		BREAK,
		CONTINUE,
}	t_state_loop;

typedef enum e_error
{
		ERR_NONE,
		ERR_SYNTAX,
		ERR_NO_FILE,
		ERR_NUM_ARG,
		ERR_TOO_MANY_ARGS,
		ERR_INVALID_OPTION,
		ERR_UNCLOSED_QUOTES,
		ERR_PERMISSION_DENIED,
}	t_error_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_files
{
	char			*name;
	char			*type;
	struct s_files	*next;
}	t_files;

typedef struct s_variable {
    char	*name;
    char	*value;
    struct s_variable *next;
} t_variable;

typedef struct s_parse
{
	char			*cmd_name;
	char			**args;
	int				builtins;
	t_files			*file;
	t_variable		*var;
	struct s_parse	*next;
}	t_parse;

int				is_numeric(char *str);
char			*ft_handle_words(char *rl, int *i);
void			ft_handle_variable(char *rl, int *i, t_token **lst, t_variable *var);
void			ft_handle_redir_out(char *rl, int *i, t_token **lst);
void			ft_handle_redir_in(char *rl, int *i, t_token **lst);
void 			ft_handle_word(char *rl, int *i, t_token **lst, t_variable *var);
char			*ft_strjoin(char *s1, char *s2);
void 			free_parse(t_parse *cmd);
void 			ft_free_token_list(t_token *lst);
int 			count_words_before_pipe(t_token *token);
char			*ft_strjoin_char(char *s1, char c);
void			ft_lstadd_back_files(t_parse **lst, t_files *new);
t_files			*ft_files_new(char *name, char *type);
int				ft_strcmp(char *str1, char *str2);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_lstsize(t_list *lst);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_token			*ft_token_new(t_token_type type, void *content);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
t_token			*ft_lstlast_token(t_token *lst);
void			sig_ign_handler(void);
void			sig_int_handler(void);
t_parse			*ft_parsing(t_token **token);
t_parse			*ft_parse_new(void);
char			*ft_strdup(char *s);
t_token 		*ft_add_cmd(char *rl);
t_parse 		*parse_piped_commands(t_token **token_p);
char			**ft_check_parse(t_token **check, t_parse **p, int *i);
int				ft_lstsize_token(t_token *token);
void			ft_builtins_check(t_parse *par);
int				f_strcmp(const char *s1, const char *s2);
t_quotes_state	ft_handle_quotes(char *rl);
t_error_type	ft_handle_error(t_parse *cmd, char *rl);
void			ft_print_list(t_parse *cmd);
int				ft_handle_arg(t_parse *cmd);
t_error_type	ft_handle_pipe(t_parse *cmd);
t_error_type 	validate_pipe_syntax(char *input);
size_t			ft_strlen(char *str);
char			*ft_strtrim(char *s1, char *set);
void			ft_print_list_2(t_token *cmd);
int 			validate_pipes(t_token *token);
void 			set_variable(char *name, char *value);
char			*ft_strchr(char *s, int c);
char			*expand_variables(const char* input);
char 			*ft_strncpy(char *dest, const char *src, size_t n);
char 			*ft_strcpy(char *dest, char *src);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			ft_handle_squote(char *rl, int *i, t_token **lst);
void			ft_handle_dquote(char *rl, int *i, t_token **lst);
void			handle_redirection(t_token **check, t_parse **p);
void			*ft_memcpy(void *dest, void *src, size_t n);
void			process_char(char *rl, int *i, t_token **lst, t_variable *var);

#endif