/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:03:53 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:44:14 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	For each environment variable
*	Separate and store the variable and the value
*		ex: USER=ysonmez
*			node->var = USER
*			node->value = ysonmez
*/

void	get_var_value(char *env, t_env *node)
{
	int	i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i] != '\0' && env[i] != '=')
	{
		i++;
	}
	node->var = (char *)malloc(sizeof(char) * (i + 1));
	if (node->var == NULL)
		return ;
	i = 0;
	while (env[i] != '\0' && env[i] != '=')
	{
		node->var[i] = env[i];
		i++;
	}
	node->var[i] = '\0';
	i++;
	node->value = ft_strdup(env + i);
}

/*	Create the shell's environment data structure
*	each node is an environment variable
*/

t_env	*env_create(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*node;

	i = 0;
	env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		node = new_node();
		if (node == NULL)
			return (NULL);
		get_var_value(envp[i], node);
		addto_lst(&env, node);
		i++;
	}
	return (env);
}
