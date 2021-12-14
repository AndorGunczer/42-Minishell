# include "../includes/minishell.h"

/*	Replaces ENV name with it's value */

void	env_to_value_lst(t_words *words, t_test *lst)
{
	while (words)
	{
		replace(words->word, ft_itoa(exit_status) ,"$?");
		words->word = path_replace(words->word, lst);
		words = words->next;
	}
}

void	env_to_value(char **words, t_test *lst)
{
	int	i;

	i = 0;
	while (words[i])
	{
		words[i] = replace(words[i], ft_itoa(exit_status) ,"$?");
		words[i] = path_replace(words[i], lst);
		ft_putendl_fd(words[i], 2);
		i++;
	}
}

/*	Determine and set route, then write the heredoc input FD
*	stored in a list into the output FD
*/

void	heredoc_output(t_words *words, t_test *lst, t_fd *fd, char *delimiter)
{
	if (lst->suffix == FILE_OUT)
	{
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(fd->outfile, 1);
		close(fd->outfile);
	}
	else if (lst->suffix == FILE_APPEND)
	{
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_APPEND, 0666);
		dup2(fd->outfile, 1);
		close(fd->outfile);
	}
	else if (lst->suffix == PIPE_OUT)
		dup2((fd->pipes)[1], 1);
	env_to_value_lst(words, lst);
	while (ft_strncmp(words->word, delimiter, ft_strlen(words->word)) != 0 || (words->word[0] == '\0'))
	{
		write(1, words->word, ft_strlen(words->word));
		ft_putchar_fd('\n', 1);
		words = words->next;
	}
}

int		route_valid(t_test *lst, int i)
{
	if (lst->suffix < 6 || lst->suffix > 9)
		*(lst->err) = PARSE_ERROR;
	else if (lst->prefix < 1 || lst->prefix > 4)
		*(lst->err) = PARSE_ERROR;
	else if ((i == 0 && lst->prefix == 3) || (lst->next == NULL && lst->suffix == 8))
		*(lst->err) = PARSE_ERROR;
	else if ((lst->prefix == HEREDOC && lst->hd_delimiter == NULL))
		*(lst->err) = PARSE_ERROR;
	else if ((lst->prefix == FILE_IN && lst->filein_path == NULL))
		*(lst->err) = FILE_MISSING;
	else if ((lst->prefix == FILE_IN && lst->filein_path != NULL &&
		lst->filein_access == FALSE))
		*(lst->err) = FILE_ACCESS;
	else if ((lst->suffix == FILE_OUT || lst->suffix == FILE_APPEND) &&
		lst->fileout_access == FALSE)
		*(lst->err) = FILE_ACCESS;
	return (PARSE_ERROR);
}

void	handle_error(t_test *lst)
{
	if (*(lst->err) == 100)
	{
		ft_putstr_fd(PARSE_ERR_MSG, 2); // 1
		exit(1);
	}
	else if (*(lst->err) == 101)
	{
		ft_putstr_fd(CMD_MISSING_MSG, 2); // 127
		exit(127);
	}
	else if (*(lst->err) == 102)
	{
		ft_putstr_fd(FILE_MISSING_MSG, 2); // 1
		exit(1);
	}
	else if (*(lst->err) == 103)
	{
		ft_putstr_fd(FILE_ACCESS_MSG, 2); // 1
		exit(1);
	}
}