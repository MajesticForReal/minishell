/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:00:55 by klaurier          #+#    #+#             */
/*   Updated: 2022/11/10 21:17:56 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define FAIL -1
# define SUCCESS 1
# define TRUE 2
# define FALSE -2

# include "minishell.h"
# include <dirent.h>
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
typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct s_utils
{
	int				i;
	int				infile;
	int				outfile;
	char			*home_str;
	int				fd_pipe[2];
}					t_utils;

typedef struct s_exec
{
	pid_t			process_id;
	int				fd_cmd[2];
	char			**cmd;
	char			**path;
	char			**file;
	char			*str_cmd;
	char			*heredoc;
	int				nb_option;
	int				nb_file_redir;
	int				cmd_size;
	int				token_before;
	struct s_exec	*next;
}					t_exec;

// utils_minishell
int					ft_compare(char *str, char *str2);
void				ft_putstr(char *str);
size_t				ft_strlen(const char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_concat2(char *str_1, char *str_2);

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
char				*ft_parsing_cd_dir(char *lex_str);
char				*ft_concat(char *str_1, char *str_2);
int					ft_builtin_cd_only(t_env *env, t_utils *utils);
int					ft_builtin_cd_back(void);
int					ft_cd_is_back(char *input);
int					ft_builtin_echo_only(void);
int					ft_builtin_env(char **envp);
void				test_signal(int code);
void				ft_builtin_echo_option(t_lex *lex);
int					ft_print_2_d_tab(char **strs, int index);
void				ft_print_2_d_tab_test(char **strs);

t_env				*ft_init_env(void);
t_env				*ft_init_fill_env(char **envp);
void				ft_fill_env(char **envp, t_env *env);
void				ft_add_back_envp(t_env *env, char **envp, int j);
void				ft_print_list_env(t_env *env);
void	ft_compare_just_a_part(char *complet_str,
							char *part_to_find,
							t_utils *utils);
void	ft_compare_just_a_part(char *complet_str,
							char *part_to_find,
							t_utils *utils);
void				ft_init_fill_str_home(char *complet_str, t_utils *builtin);
int					ft_builtin_cd_rac(void);
void				ft_export_var(t_lex *lex, t_env *env);
void				ft_add_back_str(t_env *env, char *str);
void				ft_unset_var(t_lex *lex, t_env *env);
void				ft_del_struct(t_env *env);
void				ft_all_builtin(t_lex *lex, t_env *env, t_utils *utils);
void				ft_builtin_cd_all(t_lex *lex, t_env *env, t_utils *utils);
void				ft_builtin_echo_all(t_lex *lex, t_env *env);
int					ft_builtin_echo_detect_n(char *lex_str);
void				ft_builtin_echo_option(t_lex *lex);
void				ft_not_n(t_lex *lex, int *valide_n);
int					ft_find_variable_in_env(char *var_env, char *lex_str);
int					ft_check_valid_export(char *lex_str);
char				*ft_init_prompt_place(t_env *env);
char				*ft_init_prompt_logname(t_env *env);

// parsing lexer
int					ft_out_2(t_lex **lex);
int					ft_out_3(t_lex **lex);
int					ft_out_elseif_2(t_lex **lex);
int					ft_out_elseif_3(t_lex **lex);
int					ft_out_if(t_lex **lex);
int					ft_in_2(t_lex **lex);
int					ft_in_22(t_lex **lex);
int					ft_in_33(t_lex **lex);
int					ft_in_3(t_lex **lex);
int					ft_in_elseif_2(t_lex **lex);
int					ft_in_elseif_3(t_lex **lex);
int					ft_in_if(t_lex **lex);
int					ft_pipe_3(t_lex *lex);
int					ft_pipe_2(t_lex *lex);
int					ft_parser_k(t_lex *lex, t_env *env);
t_lex				*ft_initialize_struct(void);
int					add_back(t_lex *start, int tok, char *input, int i);
int					ft_size_str(char *input, int i, char c);
void				ft_lexer(char *input, t_lex *lex);
int					ft_word(char *input, t_lex *lex, int i);
int					ft_first_lex(t_lex *lex, char *input);
int					ft_size_str_word(char *input, int i);
void				ft_parser_doll(t_lex *lex, t_env *env);
int					ft_parser(t_lex *lex);
void				ft_tok_fromfrom(t_lex **lex);
void				ft_tok_toto(t_lex **lex);
int					ft_quotes(t_lex *lex);
int					ft_out(t_lex **lex);
int					ft_in(t_lex **lex);
int					ft_pipe(t_lex *lex, t_lex *start);
int					ft_check_quotes(t_lex *lex);
int					ft_check_quotes2(t_lex *lex);

// Organizer
void				ft_organizer(t_lex **lex);
void				ft_print_list(t_lex *lex);
void				ft_concat_clear(t_lex **lex);
void				ft_clear_quotes(t_lex **lex);
void				ft_clear_quotes2(t_lex **lex, t_lex *lex_tmp);
t_lex				*ft_initialize_struct2(char *str1, char *str2, t_lex *next);
void				ft_check_dq(t_lex **lex);
void				ft_check_sq(t_lex **lex);
void				ft_concat_clear2(t_lex **lex, t_lex *first);
void				ft_concat_clear3(t_lex **lex, t_lex *first, t_lex *start);

//parser_dollar
int					ft_dollars_only(t_lex *lex);
void				ft_dollar(t_lex *lex, t_env *env);
void				ft_dollar_2(t_lex *lex, t_env *env);
void				ft_print_dollars_only(t_lex *lex);
int					ft_is_num(char *lex_str);
int					ft_dollar_is_var(char *lex_str, t_env *env);
int					ft_shearch_var(char *lex_str, t_env *env);
void				ft_print_lex_k(t_lex *lex);
void				ft_print_var(t_lex *lex, t_env *env);
void				ft_print_after_var(t_lex *lex, t_env *env);
int					ft_compare_just_a_part_2(char *var_more);
char				*ft_cut_var_more(char *var_more);
int					ft_char_after_var(t_lex *lex);
void				ft_change_list_to_var(t_lex *lex);
int					ft_after_doll_is_num(t_lex *lex);
void				ft_cut_after_1_num(t_lex *lex);
void				ft_change_list_to_var_2(t_lex *lex);
void				ft_dollar_first(t_lex *lex, t_env *env);
void				ft_change_doll_egal(t_lex *lex);
int					ft_shearch_special_char(t_lex *lex);
int					ft_var_in_env(char *var_only);
void				ft_free_tmp_list_to_var(t_lex *lex, t_lex *tmp);
void				ft_free_after_1_num(t_lex *lex);
void				ft_cut_after_special_char2(t_lex *lex, int i);
void				ft_free_after_special_char2(t_lex *lex);
void				ft_free_doll_egal(t_lex *lex);
void				ft_write_var_env_in_fd2(char *input, int fd, int i);
int					ft_write_var_env_in_fd3(char *concat, char *getenv_result,
						int j, int i);
void				ft_write_var_env_in_fd4(char *concat, char *input, int k,
						int i);
void				ft_free_write_var_fd(char *concat, char *str, int fd);
int					ft_last_alpha_num(t_lex *lex);
void				ft_cut_after_special_char(t_lex *lex);
void				ft_supp_2_list(t_lex *lex);

//heredoc
void				ft_heredoc(t_lex *lex);
void				ft_organizer_heredoc(char *input, int fd);
void				ft_dollar_heredoc(char *input, int fd);
void				ft_write_var_env_in_fd(char *input, int fd);
char				*ft_parser_limiter(t_lex *tmp);

//redirection
void				ft_redirection(t_lex *lex);
void				ft_free(t_lex *lex, t_env *env, t_utils *utils,
						t_exec *exec);

// Organizer exec
void				ft_organizer_exec(t_lex *lex, t_exec *exec, t_env *env);
char				*ft_malloc_option(t_lex *lex);
void				ft_bzero_exec(t_exec *exec);
void				ft_exec_tok_in(t_lex *lex, t_exec *exec);
t_exec				*ft_initialize_struct_exec(void);
void				ft_next_exec(t_exec *exec);
void				ft_malloc_option_execve(t_lex *lex, t_exec *exec);
void				ft_init_fill_exec(t_lex *lex, t_exec *exec, t_env *env);
void				ft_fill_tab_cmd(t_lex *lex, t_exec *exec);
void				ft_malloc_tab_file(t_lex *lex, t_exec *exec);
void				ft_malloc_tab_file_heredoc(t_lex **lex, t_exec *exec);
void				ft_fill_tab_file(t_lex *lex, t_exec *exec);
void				ft_fill_tab_file2(t_lex **lex, t_exec *exec, int *i);
void				ft_fill_tab_file3(t_lex **lex, t_exec *exec, int *i);
void				ft_malloc_heredoc_str(t_exec *exec);
char				*ft_find_path(t_env *env);
int					ft_heredoc2(char *input, char *limiter, int fd);
void				ft_heredoc0(t_lex **tmp);
void				ft_print_1_exec(t_exec *exec);
void				ft_print_2_exec(t_exec *exec);
void				ft_print_3_exec(t_exec *exec);

// NORME
int					ft_first_lex_concat(t_lex *lex, char *input, int i,
						int size);
void				ft_first_lex_token(t_lex *lex, char *input, int i);

void				ft_print_exec(t_exec *exec);

// EXEC
void				ft_exec(t_exec *exec, t_env *env, t_utils *utils,
						t_lex *lex);
void				ft_exec_no_pipe(t_exec *exec, t_env *env, t_utils *utils,
						t_lex *lex);
void				ft_init_fd_cmd(t_exec *exec);
int					ft_check_builtin(t_exec *exec);
int					ft_count_redir(t_exec *exec, char c);
int					ft_count_redir_toto(t_exec *exec, char c);
int					ft_open_toto(t_exec *exec, t_utils *utils);
int					ft_open_in(t_exec *exec, t_utils *utils);
int					ft_open_out(t_exec *exec, t_utils *utils);
int					ft_no_pipe_redir(t_exec *exec, t_utils *utils);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat_path(char *dest, char *src);
char				*ft_strdup(const char *s);
char				*ft_strdup_prog(const char *s);
void				ft_exec_pipe(t_exec *exec, t_utils *utils, t_env *env,
						t_lex *lex);
int					ft_pipe_redir(t_exec *exec, t_utils *utils);
void	ft_processus_no_pipe(t_exec *exec,
							t_env *env,
							t_utils *utils);
void				ft_exec_prog(t_exec *exec);
void				ft_constructor_cmd(t_exec *exec);
void				ft_exec_prog_cwd(t_exec *exec, char *cmd_base);
void				ft_processus_pipe(t_exec *exec, t_env *env, t_lex *lex,
						t_utils *utils);
void				ft_connect_redir(t_exec *exec, t_utils *utils);
void				ft_connect_fd_cmd(t_exec *exec);
void				ft_waitpid(t_exec *exec);

int					ft_check_str(char *str, int i);

#endif