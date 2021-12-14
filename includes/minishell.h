/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:29:48 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/11 19:28:31 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/*
*		INT MIN : -2147483648
*		INT MAX : 2147483647
*/

// # include "../libft/libft.h"
# include "../ft_lib/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>

/*	Prefix */
# define FILE_IN 1
# define STDIN 2
# define PIPE_IN 3
# define HEREDOC 4

/*	Suffix */
# define FILE_OUT 6
# define STDOUT 7
# define PIPE_OUT 8
# define FILE_APPEND 9

# define TRUE 1
# define FALSE 0

# define PARSE_ERROR 100
# define PARSE_ERR_MSG "Parse error"

# define CMD_MISSING 101
# define CMD_MISSING_MSG "Command cannot be found"

# define FILE_MISSING 102
# define FILE_MISSING_MSG "No such file or directory"

# define FILE_ACCESS 103
# define FILE_ACCESS_MSG "File cannot be accessed"

int			exit_status;

// TEST
typedef struct s_words{
	char			*word;
	struct	s_words	*next;
}	t_words;

typedef struct s_test {
	int		*content;
	char	**cmd;
	char	*bin_path;
	char	*filein_path;
	char	*fileout_path;
	char	*hd_delimiter;
	int		suffix;
	int		prefix;
	int		builtin;
	int		filein_access;
	int		fileout_access;
	int		*err;
	t_words	*env;
	struct	s_test	*next;
}	t_test;
// TEST

/*	Struct for file descriptors */
typedef struct s_fd {
	int	infile;
	int	outfile;
	int	pipes[2];
	int	temp_fd;
}	t_fd;

/*	exec_main.c */
void	pipex(t_test *lst, char **envp);

/*	exec_task.c */
void	execute_task(t_test *lst, char **envp, t_fd *fd);

/*	exec_route.c */
void	sourceof_in_out(t_test *lst, t_fd *fd);

/*	exec_utils.c */
void	env_to_value_lst(t_words *words, t_test *lst);
void	env_to_value(char **words, t_test *lst);
void	heredoc_output(t_words *words, t_test *lst, t_fd *fd, char *delimiter);
int		route_valid(t_test *lst, int i);
void	handle_error(t_test *lst);

/*	env_create.c */
char	*ft_getenv(char *str, t_words *lst);
t_words	*env_create(char **envp);

/*	pwd.c */
int		arrlen(char **arr);
void	pwd(t_test *lst);

/*	dollar_sign.c */
char	*path_replace(char *str, t_test *env);
char	*replace(char *str, char *src, char *dst);

#endif