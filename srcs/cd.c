/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:33 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:42:48 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Return the value of the "HOME" environment var in the env list */

static char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, "HOME"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*	Built-in command, replace the "PWD" environment variable by
*	the one specified by the parameter passed to 'cd'
*	and change the current directory
*/

void	ft_cd(t_list	*lst)
{
	t_env	*tmp;
	char	*home;
	int		err;

	if (lst->cmd[1] != NULL && lst->cmd[2] != NULL)
		return ;
	tmp = lst->env;
	home = get_home(tmp);
	if (lst->cmd[1] == NULL || ft_strcmp(lst->cmd[1], "~"))
		err = chdir(home);
	else
		err = chdir(lst->cmd[1]);
	if (err != 0)
		return ;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, "PWD"))
			break ;
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = getcwd(tmp->value, PATH_MAX);
	if (tmp->value == NULL)
		tmp->value = ft_strdup("");
}
