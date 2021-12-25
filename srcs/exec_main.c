/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:28 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:44:34 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	exec_main.c is the core of the "exec" filegroup */

/*	Objective of the "exec" filegroup is to prepare the input for execution of the task,
*	to determine and then set the directions of in- and output, lastly, to execute the task
*		Order of execution: exec_main.c -> exec_route.c -> exec_task.c
*/

/*	When every task is carried out, closes all pipes so that
*	file descriptor leaks are prevented
*/

static void	close_pipes(t_fd *fd)
{
	close(fd->infile);
	close(fd->outfile);
	close(fd->pipes[0]);
	close(fd->pipes[1]);
	close(fd->temp_fd);
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);
}

/* Child Process */

static void	child(t_list *lst, t_fd *fd, char **envp)
{
	close(fd->pipes[0]);
	if (*(lst->err) > 0 && *(lst->err) != 101)
		handle_error(lst);
	else
		sourceof_in_out(lst, fd);
	if (*(lst->err) == 101)
		handle_error(lst);
	else
		execute_task(lst, envp, fd);
	close(fd->pipes[1]);
	exit(0);
}

/* Parent Process */

static void	parent(t_fd *fd, int pid)
{
	close(fd->pipes[1]);
	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	close(fd->temp_fd);
	fd->temp_fd = dup(fd->pipes[0]);
	close(fd->pipes[0]);
}

/*	Main execution block of the exec filegroup */

void	pipex(t_list *lst, char **envp)
{
	t_fd	fd;
	int		pid;
	int		i;
	t_list *tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		route_valid(tmp, i++);
		if (tmp->cmd)
			env_to_value(tmp->cmd, tmp);
		if (pipe(fd.pipes) < 0)
			exit (1);
		if ((pid = fork()) < 0)
			exit(1) ;
		else if (pid == 0)
			child(tmp, &fd, envp);
		else
			parent(&fd, pid);
		tmp = tmp->next;
	}
	close_pipes(&fd);
}
