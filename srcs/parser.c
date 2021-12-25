/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:51:38 by home              #+#    #+#             */
/*   Updated: 2021/12/24 17:24:37 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Realloc the initial array (user input separate by space as delim)
*	after each node creation, in order to remove prefix and user input
*	until suffix (excluded)
*/

static char	**realloc_arr(char **arr, int start)
{
	char		**new;
	int			i;
	int			count;

	i = 0;
	if (arr == NULL)
		return (NULL);
	count = count_str(arr);
	if (start >= count || start == count - 1)
	{
		ft_memfreeall((void **)arr);
		return (NULL);
	}
	new = (char **)malloc(sizeof(char *) * (count - start + 1));
	if (new == NULL)
	{
		ft_memfreeall((void **)arr);
		return (NULL);
	}
	while (arr[start + i] != NULL)
	{
		new[i] = ft_strdup(arr[start + i]);
		i++;
	}
	new[i] = NULL;
	ft_memfreeall((void **)arr);
	return (new);
}

/*	Fill each node's data
*		i : prefix operator index (end)
*/

static void	fill_data(t_list *node, char **arr, int i)
{
	if (node->prefix == -1 && node->suffix == -1)
		get_fix(node, arr, i);
	if (node->cmd == NULL && node->prefix != HEREDOC && node->prefix != FILE_IN)
	{
		get_cmd(node, arr, i);
		//handle_quotes(node);
	}
	if (node->cmd != NULL)
		is_builtin(node);
	if (node->cmd != NULL && node->builtin == false && node->bin_path == NULL)
	{
		is_full_path(node);
		get_bin_path(node, 0);
	}
	if (node->prefix == FILE_IN || node->suffix == FILE_OUT || node->suffix == FILE_APPEND)
		get_file_path(node, arr, i);
	if (node->filein_path != NULL || node->fileout_path != NULL)
		is_file_accessible(node);
	if (node->prefix == HEREDOC && node->hd_delimiter == NULL)
		heredoc_delimiter(node, arr);
}

/*	Set defaults values for the parser's data structure */

static void	init_data(t_list *node, char *readline, int *err, t_env *env)
{
	node->env = env;
	node->cmd = NULL;
	node->bin_path = NULL;
	node->filein_path = NULL;
	node->fileout_path = NULL;
	node->hd_delimiter = NULL;
	node->err = err;
	node->readline = readline;
	node->prefix = -1;
	node->suffix = -1;
	node->builtin = false;
	node->filein_access = false;
	node->fileout_access = false;
}

/*	Parse the user input :
*		Separate each commands (Tokenization)
*		Each Token :
*			- contains = cmd, flags, inputs, path of the binary..
*			- is a node in the linked list
*/

t_list	*parser(char *cmd, int *err, t_env *env)
{
	t_list	*list;
	t_list	*node;
	char	**arr;
	int		i;

	i = 0;
	arr = space_fix(ft_split(cmd, ' '));
	list = NULL;
	while (arr[i] != NULL)
	{
		if ((i > 0 && is_opt(arr[i])) || arr[i + 1] == NULL)
		{
			node = ft_lstnew();
			if (node == NULL)
				return (NULL);
			init_data(node, cmd, err, env);
			fill_data(node, arr, i);
			ft_lstadd_back(&list, node);
			if (node->suffix == FILE_OUT || node->suffix == FILE_APPEND)
				i += 2;
			arr = realloc_arr(arr, i);
			if (arr == NULL)
				break ;
			i = -1;
		}
		i++;
	}
	if (list == NULL)
	{
		list = ft_lstnew();
		init_data(list, cmd, err, env);
	}
	return (list);
}
