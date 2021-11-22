#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdarg.h>

int	main(int argc, char **argv, char **envp);

void	pipex(t_list *lst, int argc, char **argv, char **envp);
// void	command(t_list *lst, int (*pipe)[2], char **envp);
// char	**assemble_cmd(char ***cmd, t_words *words);
// void	sourceof_in_out(t_list *lst, int (*pipe)[2], int *in, int *out);

void	file_in_file_out(int (*pipe)[2], int *in, int *out);
void	file_in_stdout(int (*pipe)[2], int *in);
void	file_in_pipe_out(int (*pipe)[2], int *in);
void	stdin_pipe_out(int (*pipe)[2]);
void	stdin_stdout(int (*pipe)[2]);
void	stdin_file_out(int (*pipe)[2], int *out);
void	pipe_in_pipe_out(int (*pipe)[2]);
void	pipe_in_stdout(int (*pipe)[2]);
void	pipe_in_file_out(int (*pipe)[2], int *out);

#endif