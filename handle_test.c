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

int	main(int argc, char **argv, char **envp)
{
	t_list *lst = ft_lstnew(2, 8, "/bin/ls -l");
	lst->next = ft_lstnew(3, 8, "/bin/ls");
	lst->next->next = ft_lstnew(3, 7, "/usr/bin/wc -l");
	pipex(lst, argc, argv, envp);
}