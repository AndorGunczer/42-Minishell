# include "../includes/minishell.h"

/*	exec_route.c determines and sets the source (stdin) and the destination (stdout)
*	of the route
*/

/*	All functions below set the source and destination according
*	to the determined route by sourceof_in_out()
*/

static void	file_in_file_out(t_fd *fd, int mode, t_test *lst)
{
	fd->infile = open(lst->filein_path, O_RDONLY);
	if (mode == FILE_OUT)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (mode == FILE_APPEND)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	dup2(fd->infile, 0);
	dup2(fd->outfile, 1);
	close(fd->infile);
	close(fd->outfile);
}

static void	file_in_stdout(t_fd *fd, t_test *lst)
{
	fd->infile = open(lst->filein_path, O_RDONLY);
	dup2(fd->infile, 0);
	close(fd->infile);
}

static void	file_in_pipe_out(t_fd *fd, t_test *lst)
{
	fd->infile = open(lst->filein_path, O_RDONLY);
	dup2(fd->infile, 0);
	dup2((fd->pipes)[1], 1);
	close(fd->infile);
}

static void	stdin_file_out(t_fd *fd, int mode, t_test *lst)
{
	if (mode == FILE_OUT)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (mode == FILE_APPEND)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	dup2(fd->outfile, 1);
	close(fd->outfile);
}

static void	stdin_pipe_out(t_fd *fd)
{
	dup2((fd->pipes)[1], 1);
}

static void	pipe_in_file_out(t_fd *fd, int mode, t_test *lst)
{
	if (mode == FILE_OUT)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (mode == FILE_APPEND)
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	dup2(fd->temp_fd, 0);
	dup2(fd->outfile, 1);
	close(fd->outfile);
}

static void	pipe_in_stdout(t_fd *fd)
{
	dup2(fd->temp_fd, 0);
}

static void	pipe_in_pipe_out(t_fd *fd)
{
	dup2(fd->temp_fd, 0);
	dup2((fd->pipes)[1], 1);
}

/*	Determines the source and destination of the route of the task
*		ex.:	from file to file = file_in_file_out
*				from stdin to pipe = stdin_in_pipe_out
*/

void	sourceof_in_out(t_test *lst, t_fd *fd)
{
	if (lst->prefix == FILE_IN)
	{
		if (lst->suffix == FILE_OUT)
			file_in_file_out(fd, FILE_OUT, lst);
		else if (lst->suffix == STDOUT)
			file_in_stdout(fd, lst);
		else if (lst->suffix == PIPE_OUT)
			file_in_pipe_out(fd, lst);
		else if (lst->suffix == FILE_APPEND)
			file_in_file_out(fd, FILE_APPEND, lst);
	}
	else if (lst->prefix == STDIN)
	{	
		if (lst->suffix == FILE_OUT)
			stdin_file_out(fd, FILE_OUT, lst);
		else if (lst->suffix == STDOUT)
			return ;
		else if (lst->suffix == PIPE_OUT)
			stdin_pipe_out(fd);
		else if (lst->suffix == FILE_APPEND)
			stdin_file_out(fd, FILE_APPEND, lst);
	}
	else if (lst->prefix == PIPE_IN)
	{
		if (lst->suffix == FILE_OUT)
			pipe_in_file_out(fd, FILE_OUT, lst);
		else if (lst->suffix == STDOUT)
			pipe_in_stdout(fd);
		else if (lst->suffix == PIPE_OUT)
			pipe_in_pipe_out(fd);
		else if (lst->suffix == FILE_APPEND)
			pipe_in_file_out(fd, FILE_APPEND, lst);
	}
}
