/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:00:55 by klaurier          #+#    #+#             */
/*   Updated: 2022/10/20 15:41:38 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define FAIL -1
# define SUCCESS 1
# define TRUE 2
# define FALSE -2

# include "minishell.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum				e_token
{
	TOK_SPACE,
	TOK_PIPE,
	TOK_DQ,
	TOK_SQ,
	TOK_IN,
	TOK_OUT,
	TOK_TOTO,
	TOK_FROMFROM,
	TOK_DOLL,
	TOK_WORD,
};

typedef struct s_lex
{
	char			*str;
	int				token;
	struct s_lex	*next;
}					t_lex;

//structure de pipex
typedef struct env
{
	char			*str;
	struct env		*next;
}					t_env;

typedef struct utils
{
	char			*home_str;
}					t_builtin;

typedef struct var
{
	char			*name;
	struct var		*next;
}					t_var;

typedef struct s_pipex
{
	int				fd_in;
	int				fd_out;
	char			**path;
	char			**cmd1;
	char			**cmd2;
	char			*my_cmd;
	char			*new_path;
	int				status_fd_in;
	int				status_fd_out;
	int				status;
	int				pipe_fd[2];
	pid_t			child;
	pid_t			child_2;

}					t_pipex;

//struct minishell
typedef struct s_minishell
{
	char			**builtin;
	int				i;
	int				j;
	int				size_pwd;
	int				size_short_input;
	char			*path_pwd;
	char			*complet_path;
	char			*short_pwd;
	char			*short_input;
}					t_minishell;

typedef struct s_lexer
{
	char			*word;
	int				token;
}					t_lexer;

// utils_minishell
int					ft_compare(char *str, char *str2);
void				ft_putstr(char *str);
size_t				ft_strlen(const char *str);

//utils pipex
void				ft_error(t_pipex *pipex, int *pipe_fd);
void				ft_free_all(t_pipex *pipex);
void				close_fd(t_pipex *pipex);
void				ft_free_2dchar(char **tab);
void				ft_execve_fail(char *my_cmd);
void				ft_exec_cmd_no_env(char **cmd, char **path, t_pipex *pipex);
void				ft_exec_cmd_env(char **cmd, char **path, t_pipex *pipex);
void				ft_dup_and_close(t_pipex *pipex, int x);
void				ft_fork_child_2(t_pipex *pipex);
void				ft_fork_child(t_pipex *pipex);
void				ft_exeptional_case_1(t_pipex *pipex, char **argv);
int					ft_detect_exeptional_case_0(char **argv, t_pipex *pipex);
int					ft_detect_exeptional_case_3(int i, int j);
int					ft_detect_exeptional_case_2(char **argv);
int					ft_detect_exeptional_case_1(char **argv);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
char				*ft_strchr(const char *str, int c);
char				*ft_strcat_cmd(char *path, char *cmd, char slash);
void				ft_putstr(char *str);
void				ft_pipex(t_pipex *pipex);
void				ft_choose_cmd(char **argv, t_pipex *pipex);
void				ft_get_fd_in(char **argv, t_pipex *pipex);
int					main_pipex(int argc, char **argv, char **envp);
void				ft_malloc_nothing(t_pipex *pipex);
int					ft_get_path_cmd(char **argv, char **envp, t_pipex *pipex);
int					ft_get_cmd(char **argv, t_pipex *pipex);
const char			*ft_search_line_path(char **envp);

//split
char				**ft_malloc_error(char **strs);
int					ft_count_words(const char *str, char c);
void				ft_words_cpy(const char *s, int *start_w, int end,
						char *strs);
char				**ft_r_split(char const *s, char c, char **strs);
char				**ft_split(char const *s, char c);

//buitin
char				*ft_builtin_pwd(int option);
int					ft_builtin_cd_dir(char *input);
char				*ft_parsing_cd_dir(char *str);
char				*ft_concat(char *str_1, char *str_2);
int					ft_builtin_cd_only(char *input, t_env *env);
int					ft_builtin_cd_back(char *input);
int					ft_cd_is_back(char *input);
int					ft_builtin_echo_option(char *input);
int					ft_builtin_echo_only(char *input);
int					ft_builtin_echo(char *input);
int					ft_builtin_env(char **envp);
void				test_signal(int code);
int					ft_builtin_echo_option_2(char *input);
int					ft_print_2_d_tab(char **strs, int index);
t_env				*ft_init_env(void);
void				ft_fill_env(char **envp, t_env *env);
void				ft_add_back_envp(t_env *env, char **envp, int j);
t_env				*ft_init_fill_env(char **envp);
void				ft_print_list_env(t_env *env);
void				ft_compare_just_a_part(char *complet_str,
						char *part_to_find, t_builtin *t_builtin);
void				ft_init_fill_str_home(char *complet_str,
						t_builtin *builtin);
int					ft_builtin_cd_rac(char *input);
void				ft_export_var(char *input, t_env *env);
void				ft_add_back_str(t_env *env, char *str);
void				ft_unset_var(char *input, t_env *env);
void				ft_del_struct(t_env *env);

// lexer
t_lex				*ft_initialize_struct(void);
int					add_back(t_lex *start, int tok, char *input, int i, char c);
int					ft_size_str(char *input, int i, char c);
void				ft_lexer(char *input, t_lex *lex);
int					ft_word(char *input, t_lex *lex, int i);
int					ft_first_lex(t_lex *lex, char *input);
int					ft_size_str_word(char *input, int i);

// parser redirection
void				ft_tok_toto(t_lex *lex);
void				ft_tok_fromfrom(t_lex *lex);
int				ft_in(t_lex *lex);
int				ft_out(t_lex *lex);
int				ft_quotes(t_lex *lex);
int				ft_pipe(t_lex *lex, t_lex *start);
void				ft_parser(t_lex *lex);

#endif