# include "./libft/libft.h"
# include "minishell.h"

void	file_in_file_out(int (*pipe)[2], int *in, int *out)
{
	// *in = open(argv[], O_RDONLY);
	// *out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	dup2(*in, 0);
	dup2(*out, 1);
	close(*pipe[0]);
	close(*pipe[1]);
	close(*in);
	close(*out);
}

void	file_in_stdout(int (*pipe)[2], int *in)
{
	// *in = open(argv[], O_RDONLY);
	dup2(*in, 0);
	close(*pipe[1]);
	close(*pipe[2]);
	close(*in);
}

void	file_in_pipe_out(int (*pipe)[2], int *in)
{
	// *in = open(argv[], O_RDONLY);
	dup2(*in, 0);
	dup2(*pipe[1], 1);
	close(*pipe[0]);
	close(*pipe[1]);
	close(*in);
}

void	stdin_file_out(int (*pipe)[2], int *out)
{
	// *out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	dup2(*out, 1);
	close(*out);
	close(*pipe[0]);
	close(*pipe[1]);
}

void	stdin_stdout(int (*pipe)[2])
{
	close(*pipe[0]);
	close(*pipe[1]);
}

void	stdin_pipe_out(int (*pipe)[2])
{
	dup2(*pipe[1], 1);
	close(*pipe[1]);
	close(*pipe[0]);
}

void	pipe_in_file_out(int (*pipe)[2], int *out)
{
	// *out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	dup2(*pipe[0], 0);
	dup2(*out, 1);
	close(*pipe[1]);
	close(*pipe[0]);
	close(*out);
}

void	pipe_in_stdout(int (*pipe)[2])
{
	dup2(*pipe[0], 0);
	close(*pipe[1]);
	close(*pipe[0]);
}

void	pipe_in_pipe_out(int (*pipe)[2])
{
	dup2(*pipe[0], 0);
	dup2(*pipe[1], 1);
	close(*pipe[0]);
	close(*pipe[1]);
}
