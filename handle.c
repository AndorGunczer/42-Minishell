# include "./libft/libft.h"
# include "minishell.h"

//PREFIX
#define FILE_IN 1
#define STDIN 2
#define PIPE_IN 3

//SUFFIX
#define FILE_OUT 6
#define STDOUT 7
#define PIPE_OUT 8

static void	sourceof_in_out(t_list *lst, int (*pipe)[2], int *in, int *out)
{
	if (lst->prefix == FILE_IN)
	{
		if (lst->suffix == FILE_OUT)
			file_in_file_out(pipe, in, out);
		else if (lst->suffix == STDOUT)
			file_in_stdout(pipe, in);
		else if (lst->suffix == PIPE_OUT)
			file_in_pipe_out(pipe, in);
	}
	else if (lst->prefix == STDIN)
	{	
		if (lst->suffix == FILE_OUT)
			stdin_file_out(pipe, out);
		else if (lst->suffix == STDOUT)
			stdin_stdout(pipe);
		else if (lst->suffix == PIPE_OUT)
			stdin_pipe_out(pipe);
	}
	else if (lst->prefix == PIPE_IN)
	{
		if (lst->suffix == FILE_OUT)
			pipe_in_file_out(pipe, out);
		else if (lst->suffix == STDOUT)
			pipe_in_stdout(pipe);
		else if (lst->suffix == PIPE_OUT)
			pipe_in_pipe_out(pipe);
	}
}
//
// int		ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
 
// int		ft_lstiter(t_list *lst, int (*f)(char *))
// {
// 	int	i;

// 	i = 0;
// 	while (lst->next != NULL)
// 	{
// 		i += f(lst->words);
// 		lst = lst->next;
// 	}
// 	i += f(lst->words);
// 	return (i);
// }
//
static char	**assemble_cmd(char ***cmd, t_words *words)
{
	int	x;
	int	size;
	int	i;

	// x = 1;
	i = 0;
	size = ft_lstsize(words);
	*cmd = ft_calloc(size + 1, sizeof(char *));
	while (words)
	{
		(*cmd)[i] = ft_strdup(words->word);
		i++;
		words = words->next;
	}
	return (*cmd);
}

static void	command(t_list *lst, int (*pipe)[2], char **envp)
{
	char	**cmd;

	cmd = assemble_cmd(&cmd, lst->words);
	execve(cmd[0], cmd, envp);
	// printf("%s \n", cmd[1]);
	// exit(0);
}

	// int i = 0;
	// while (cmd[i] != '\0')
	// {
	// 	printf("|%s|\n", cmd[i]);
	// 	i++;
	// }

void	pipex(t_list *lst, int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;
	int	pid;
	int	pipes[2];

	while (lst)
	{
		if (pipe(pipes) < 0)
			exit (1);
		sourceof_in_out(lst, &pipes, &fd1, &fd2);
		pid = fork();
		if (pid == 0)
			command(lst, &pipes, envp);
		else
		{
			wait(0);
		}
		lst = lst->next;
	}
}
