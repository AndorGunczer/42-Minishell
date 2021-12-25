/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_task.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:53 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:44:56 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static void	command(t_list *lst, char **envp, t_fd *fd)
{
	execve(lst->bin_path, lst->cmd, envp);
	close(fd->pipes[1]);
	exit(127);
}

/*	PROTOTYPE */

void	builtin(t_list *lst)
{
	if (is_same(lst->cmd[0], "echo") == 1)
		ft_echo(lst);
	else if (is_same(lst->cmd[0], "cd") == 1)
		ft_cd(lst);
	else if (is_same(lst->cmd[0], "pwd") == 1)
		ft_pwd(lst);
	else if (is_same(lst->cmd[0], "export") == 1)
		ft_export(lst);
	else if (is_same(lst->cmd[0], "unset") == 1)
		ft_unset(lst);
	else if (is_same(lst->cmd[0], "env") == 1)
		ft_env(lst);
	// else if (is_same(lst->cmd[0], "exit") == 1)
	// 	ft_exit(lst);
}

/*	Read from source FD into dest FD */

static void	read_into()
{
	char	str[2];

	while (1)
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

static void	heredoc(char *delimiter, t_list *lst, t_fd *fd) // double code interpretation (only $)
{
	char	*str;
	int		x;
	t_words	*words;
	t_words *tmp;

	x = 1;
	while (1) // str != NULL && (ft_strncmp(str, delimiter, ft_strlen(str)) != 0 || str[0] == '\0')
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
	lst_clear_words(&words);
	// ft_lstclear(&words, &free); // requires change in libft
}

/* Decide which task to execute based on in- and out FD */

void	execute_task(t_list *lst, char **envp, t_fd *fd)
{
	if (lst->prefix == FILE_IN)
		read_into();
	else if (lst->prefix == HEREDOC)
		heredoc(lst->hd_delimiter, lst, fd);
	else if (lst->builtin == 1)
		builtin(lst);
	else
		command(lst, envp, fd);
}

/*	I'm sorry but I'm biologist, son of Ragnar Lodbrok */