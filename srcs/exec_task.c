# include "../includes/minishell.h"

//test

static t_words	*ft_wordsnew(void *content)
{
	t_words	*new_struct;

	new_struct = malloc(sizeof(t_words));
	if (new_struct == 0)
		return (0);
	new_struct->word = content;
	new_struct->next = NULL;
	return (new_struct);
}

/*	Executes the command */

static void	command(t_test *lst, char **envp, t_fd *fd)
{
	execve(lst->bin_path, lst->cmd, envp);
	close(fd->pipes[1]);
	exit(127);
}

/*	PROTOTYPE */

// void	builtin()
// {
// 	if (ft_strncmp(lst->words->word, "echo") == 0)
// 		echo();
// 	else if (ft_strncmp(lst->words->word, "cd") == 0)
// 		cd();
// 	else if (ft_strncmp(lst->words->word, "pwd") == 0)
// 		pwd();
// 	else if (ft_strncmp(lst->words->word, "export") == 0)
// 		export();
// 	else if (ft_strncmp(lst->words->word, "unset") == 0)
// 		unset();
// 	else if (ft_strncmp(lst->words->word, "env") == 0)
// 		env();
// 	else if (ft_strncmp(lst->words->word, "exit") == 0)
// 		exit_cust();
// }

/*	Read from source FD into dest FD */

static void	read_into()
{
	char	str[2];

	while (TRUE)
	{
		str[1] = '\0';
		if (read(0, str, 1) <= 0)
			break;
		write(1, str, 1);
	}
}

/*	Read an input stream literal until delimiter from source FD into dest FD
*	NOTE: Behaves differently from general behavior of the program,
*	since readfile() writes to stdout, redirections don't happen in exec_route.c, but
*	in exec_utils.c -> heredoc_output() called at the end of heredoc()
*/

static void	heredoc(char *delimiter, t_test *lst, t_fd *fd) // double code interpretation (only $)
{
	char	*str;
	int		x;
	t_words	*words;
	t_words *tmp;

	x = 1;
	while (TRUE) // str != NULL && (ft_strncmp(str, delimiter, ft_strlen(str)) != 0 || str[0] == '\0')
	{
		if (lst->suffix == PIPE_OUT)
			str = readline("pipe heredoc>");
		else
			str = readline("heredoc>");
		if (x-- == 1)
		{
			tmp = ft_wordsnew(str);
			words = tmp;
		}
		else
		{
			tmp->next = ft_wordsnew(str);
			tmp = tmp->next;
		}
		if (str == NULL || (ft_strncmp(str, delimiter, ft_strlen(str)) == 0 && str[0] != '\0'))
			break ;
	}
	heredoc_output(words, lst, fd, delimiter);
	// ft_lstclear(&words, &free); // requires change in libft
}

/* Decide which task to execute based on in- and out FD */

void	execute_task(t_test *lst, char **envp, t_fd *fd)
{
	if (lst->prefix == FILE_IN)
		read_into();
	else if (lst->prefix == HEREDOC)
		heredoc(lst->hd_delimiter, lst, fd);
	else
		command(lst, envp, fd);
}

/*	I'm sorry but I'm biologist, son of Ragnar Lodbrok */