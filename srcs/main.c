/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:23:11 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 17:26:18 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Print each node's data for testing purpose */
void print_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("___________________\n");
}

/*	Print each node's data for testing purpose */
void print_data(t_list	*lst)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = lst;
	while(tmp != NULL)
	{
		printf("______________________________________\n");
		if (tmp->cmd != NULL)
		{
			while(tmp->cmd[i] != NULL)
			{
				if (i == 0)
					printf("cmd[%d] %s\t", i, tmp->cmd[i]);
				else
					printf("flag[%d] %s\t", i, tmp->cmd[i]);
				i++;
			}
			printf("\n");
		}
		i = 0;
		printf("is builtin?\t%d\n", tmp->builtin);
		printf("binpath\t%s\n", tmp->bin_path);
		printf("prefix\t%d\n", tmp->prefix);
		printf("suffix\t%d\n", tmp->suffix);
		printf("file_in_path\t%s\n", tmp->filein_path);
		printf("file_out_path\t%s\n", tmp->fileout_path);
		printf("file_in_acces\t%d\n", tmp->filein_access);
		printf("file_out_acces\t%d\n", tmp->fileout_access);
		printf("heredoc delim\t%s\n", tmp->hd_delimiter);
		printf("ERROR \t%d\n", *(tmp->err));
		tmp = tmp->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_list	*data;
	t_env	*env;
	char	*cmd;
	int		err;

	(void)argv;
	if (argc != 1 && ft_putendl_fd("Launch minishell without arguments", 1))
		return (1);
	err = 0;
	env = env_create(envp);
	while (1)
	{
		cmd = readline("➔   ");
		if (cmd == NULL)
			continue ;
		data = parser(cmd, &err, env);
		//if (data == NULL && lst_clear_data(&data) && lst_clear_env(&env))
		//	return (1);
		pipex(data, envp);
		if (ft_strcmp(cmd, "") != 0)
			add_history(cmd);
		//lst_clear_data(&data);
		if (err != 0)
			err = 0;
	}
	//clear_env here ? depend on signal handling
	return (0);
}
