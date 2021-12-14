/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:23:11 by ysonmez           #+#    #+#             */
/*   Updated: 2021/11/11 16:08:46 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_test	*ft_lstnewtest(char *command, char *bin_path, char	*filein_path, char *fileout_path, char *hd_delimiter, int prefix, int suffix, int builtin, int filein_access, int fileout_access, t_words *env)
{
	t_test	*new_struct;

	new_struct = malloc(sizeof(t_test));
	if (new_struct == 0)
		return (0);
	new_struct->content = 0;
	new_struct->cmd = ft_split(command, ' ');
	new_struct->bin_path = bin_path;
	new_struct->filein_path = filein_path;
	new_struct->fileout_path = fileout_path;
	new_struct->hd_delimiter = hd_delimiter;
	new_struct->prefix = prefix;
	new_struct->suffix = suffix;
	new_struct->builtin = builtin;
	new_struct->filein_access = filein_access;
	new_struct->fileout_access = fileout_access;
	new_struct->next = NULL;
	new_struct->err = NULL;
	new_struct->env = env;
	return (new_struct);
}

int	main(int argc, char **argv, char **envp)
{
	t_test *lst;
	t_words *env = env_create(envp);
	// lst = ft_lstnewtest("env", "/usr/bin/env", "infile", NULL, NULL, 2, 8, 0, 0, 0, env);
	// argc = 0;
	// argv++;
	// envp++;
	// char *fuck = "PATH";
	// char *you = "PWD";
	// char *str = ft_getenv(fuck, lst->env);
	// char *sec = ft_getenv(you, lst->env);
	// printf("%s\n", str);
	// printf("%s", sec);

	// char *str = "mi ez: $?";
	// char *rep = "5";
	// int i = 5;
	// str = replace(str, ft_itoa(i), "$?");
	// printf("%s", str);
	// int x = contains("t", "");
	// printf("%d", x);

	exit_status = 0;
	lst = ft_lstnewtest("env", "/usr/bin/env", "infile", NULL, NULL, 2, 8, 0, 0, 0, env);
	lst->next = ft_lstnewtest("grep $PWD$?$PWD", "/usr/bin/grep", NULL, NULL, NULL, 3, 7, 0, 0, 0, env);
	
	// lst->next->next = ft_lstnewtest("ls -l", "/bin/ls", NULL, NULL, NULL, 2, 7, 0, 0, 0, env);
	// lst->next->next->next = ft_lstnew(3, 6, "/bin/cat");
	pipex(lst, envp);
	// printf("len dst: %d\nlen src: %d\nlen total_str: %zu\nlen total_ret: %d", len_dst, len_src, ft_strlen(str), len_new);
}