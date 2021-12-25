/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:29:48 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:55:23 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/*
*		INT MIN : -2147483648
*		INT MAX : 2147483647
*/

/*	Our lovely prompt 四ボールオメガシェル ➔ */

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

/*	Prefix and Suffix, from where we read to where we write */

typedef enum e_fix
{
	FILE_IN		=	1,
	STDIN		=	2,
	PIPE_IN		=	3,
	HEREDOC		=	4,
	FILE_OUT	=	6,
	STDOUT		=	7,
	PIPE_OUT	=	8,
	FILE_APPEND	=	9
}	t_fix;

/*	ERROR MACRO */

# define PARSE_ERROR 100
# define PARSE_ERR_MSG "Parse error\n"

# define CMD_MISSING 101
# define CMD_MISSING_MSG "Command cannot be found\n"

# define FILE_MISSING 102
# define FILE_MISSING_MSG "No such file or directory\n"

# define FILE_ACCESS 103
# define FILE_ACCESS_MSG "File cannot be accessed\n"

# define TRUE 1
# define FALSE 0

int	exit_status;

/*	list to scalably store a series of *strings */

typedef struct s_words{
	char			*word;
	struct s_words	*next;
}	t_words;

/*	struct to store file descriptors */

typedef struct s_fd {
	int	infile;
	int	outfile;
	int	pipes[2];
	int	temp_fd;
}	t_fd;

/*	List to store the shell's own env
*	each node is a different env var
*	with var and value (ex: var=USER, value=ysonmez)
*/

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

/*	List to store the parsed user input data
*	Prepared for execution
*/

typedef struct s_list
{
	t_env		*env;
	int			*err;
	char		*readline;
	char		**cmd;
	char		*bin_path;
	char		*filein_path;
	char		*fileout_path;
	char		*hd_delimiter;
	int			suffix;
	int			prefix;
	bool		builtin;
	bool		filein_access;
	bool		fileout_access;
	struct s_list	*next;
}	t_list;


/*	parser.c */
t_list	*parser(char *cmd, int *err, t_env *env);

/*	syntax.c */
void	get_cmd(t_list *node, char **arr, int i);
void	handle_quotes(t_list *node);
void	is_builtin(t_list *node);
void	is_full_path(t_list *node);
void	get_bin_path(t_list *node, int i);
void	get_fix(t_list *node, char **arr, int i);
void	get_file_path(t_list *node, char **arr, int i);
void	is_file_accessible(t_list *node);
void	heredoc_delimiter(t_list *node, char **arr);

/*	utils.c */
int	is_opt(char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	**space_fix(char **arr);


int		count_str(char **arr);

/*	env_lst.c */
void	get_var_value(char *env, t_env *node);
t_env	*env_create(char **envp);

/*	lst_utils.c */
t_env	*new_node(void);
t_list	*ft_lstnew(void);
void	addto_lst(t_env **lst, t_env *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

/*	Built-in commands */
void	ft_cd(t_list	*lst);
void	ft_echo(t_list	*lst);
void	ft_env(t_list	*lst);
void	ft_exit(t_list	*lst);
void	ft_export(t_list	*lst);
void	ft_pwd(t_list	*lst);
void	ft_unset(t_list	*lst);

/*	exec_main.c */
void	pipex(t_list *lst, char **envp);

/*	exec_task.c */
void	execute_task(t_list *lst, char **envp, t_fd *fd);

/*	exec_route.c */
void	sourceof_in_out(t_list *lst, t_fd *fd);

/*	exec_utils.c */
void	env_to_value_lst(t_words *words, t_list *lst);
void	env_to_value(char **words, t_list *lst);
void	heredoc_output(t_words *words, t_list *lst, t_fd *fd, char *delimiter);
int		route_valid(t_list *lst, int i);
void	handle_error(t_list *lst);

/*	env_create.c */
char	*ft_getenv(char *str, t_env *lst);
t_env	*env_create(char **envp);
int		is_same(char *str, char *src);

/*	dollar_sign.c */
char	*path_replace(char *str, t_list *env);
char	*replace(char *str, char *src, char *dst);

/*	free.c	*/
void	lst_clear_words(t_words **lst);
int		lst_clear_env(t_env **env);
int		lst_clear_data(t_list **lst);


/*	TESTING PURPOSE TO REMOVE */
void print_data(t_list	*lst);
void print_arr(char **arr);
# define PRINT_HERE() (printf("file: %s, line: %d\n", __FILE__, __LINE__));

#endif
