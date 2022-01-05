/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:44:25 by ysonmez           #+#    #+#             */
/*   Updated: 2022/01/04 16:27:07 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Get the actual command
*/

void	get_cmd(t_list *node, char **arr, int i)
{
	int	j;

	if (arr == NULL || (is_opt(arr[0]) && arr[1] == NULL))
		return ;
	if (i == 0)
	{
		node->cmd = (char **)malloc(sizeof(char *) * 2);
		node->cmd[0] = ft_strdup(arr[0]);
		node->cmd[1] = NULL;
		return ;
	}
	if (arr[i + 1] == NULL)
		i++;
	if (node->prefix == FILE_IN || node->prefix == HEREDOC)
	{
		node->cmd = (char **)malloc(sizeof(char *));
		node->cmd[0] = NULL;
		return ;
	}
	node->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		if (node->prefix == STDIN)
			node->cmd[j] = ft_strdup(arr[j]);
		else if (arr[j + 1] != NULL && is_opt(arr[j + 1]) == 0)
			node->cmd[j] = ft_strdup(arr[j + 1]);
		else
			node->cmd[j] = NULL;
		j++;
	}
	node->cmd[j] = NULL;
}

/*	Handle double and simple quotes, by restructuring the user input
*/
/*
void	handle_quotes(t_list *node)
{
	char	**arr;
	int		i;

	i = 0;
	if (node->prefix == STDIN)
		i = 0;
	else
		i = 1;
	arr = ft_split(&node->readline[i], '"');
	free(arr[0]);
	arr[0] = ft_strdup(node->cmd[0]);
	i = 0;
	//while (arr[])
	//ft_memefreeall((void **)node->cmd)
	node->cmd = arr;
}
*/
/*	Check if the command is a shell builtin command or not
*		Builtin : (cd; echo; env; exit; export; pwd; unset)
*/

void	is_builtin(t_list *node)
{
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "echo") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "env") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "exit") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "export") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "pwd") == 0)
		node->builtin = true;
	else if(ft_strcmp(node->cmd[0], "unset") == 0)
		node->builtin = true;
	else
		node->builtin = false;
}

/*	Check if the full apth of the command was provided */

void	is_full_path(t_list *node)
{
	char	**tmp;
	char	*buff;
	int		i;

	i = 0;
	if (ft_strchr(node->cmd[0], '/') != NULL)
	{
		tmp = ft_split(node->cmd[0], '/');
		while (tmp[i] != NULL)
		{
			i++;
		}
		i--;
		free(node->cmd[0]);
		buff = ft_strdup(tmp[i]);
		node->cmd[0] = buff;
		ft_memfreeall((void **)tmp);
	}
	else
		return ;
}

/*	Return the exact path where the command's binary is in the filesystem.
*	Protected against env -i and against not found command
*/

void	get_bin_path(t_list *node, int i)
{
	char	*env;
	char	*buff;
	char	**tmp;
	char	*path;

	env = getenv("PATH");
	if (env == NULL)
		env = "/Users/$(USER)/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	buff = ft_strjoin("/", node->cmd[0]);
	tmp = ft_split(env, ':');
	while (tmp[i] != NULL)
	{
		path = ft_strjoin(tmp[i], buff);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
		if (tmp[i] == NULL)
		{
			*(node->err) = 101;
			ft_memfreeall((void **)tmp); /*?*/
			return ;
		}
	}
	free(buff);
	ft_memfreeall((void **)tmp); /*?*/
	node->bin_path = path;
}

/*	Separation of each command is based on the suffix and prefix
*		prefix can be : stdin, file_in, pipe_in or heredoc
*		suffix can be : stdout, pipe_out, file_out, file_append
*	>> From where we get data to where we redirect it after execution
*/

void	get_fix(t_list *node, char **arr, int i)
{
	if (ft_strcmp(arr[0], "|") == 0)
		node->prefix = PIPE_IN;
	else if (ft_strcmp(arr[0], "<") == 0)
		node->prefix = FILE_IN;
	else if (ft_strcmp(arr[0], "<<") == 0)
		node->prefix = HEREDOC;
	else if (ft_strcmp(arr[0], ">") == 0)
		node->prefix = FILE_OUT;
	else if (ft_strcmp(arr[0], ">>") == 0)
		node->prefix = FILE_APPEND;
	else
		node->prefix = STDIN;
	if (ft_strcmp(arr[i], "|") == 0)
		node->suffix = PIPE_OUT;
	else if (ft_strcmp(arr[i], ">") == 0)
		node->suffix = FILE_OUT;
	else if (ft_strcmp(arr[i], ">>") == 0)
		node->suffix = FILE_APPEND;
	else
		node->suffix = STDOUT;
}

/*	In case we need to read/write in a file,
*	get the file path and store it for eecution
*/

void	get_file_path(t_list *node, char **arr, int i)
{
	if (node->prefix == FILE_IN)
	{
		node->filein_path = ft_strdup(arr[1]);
	}
	if (arr[i + 1] != NULL && (node->suffix == FILE_OUT || node->suffix == FILE_APPEND))
	{
		node->fileout_path = ft_strdup(arr[i + 1]);
	}
}

/*	In case we need to read/write in a file,
*	check if the file is accessible (if it already exists)
*	to avoid overwriting
*/

void	is_file_accessible(t_list *node)
{
	if (node->filein_path != NULL)
	{
		if (access(node->filein_path, F_OK) == 0)
			node->filein_access = true;
		else
			node->filein_access = false;
	}
	else if (node->fileout_path != NULL)
	{
		if (access(node->fileout_path, F_OK) == 0)
			node->fileout_access = true;
		else
			node->fileout_access = false;
	}
}

/*	if HEREDOC, get the delimiter */

void	heredoc_delimiter(t_list *node, char **arr)
{
	if (arr != NULL && arr[1] != NULL && arr[2] == NULL)
		node->hd_delimiter = ft_strdup(arr[1]);
}
