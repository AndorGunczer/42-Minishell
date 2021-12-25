/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:51 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:45:47 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Remove the specified environment variable
*		(Remove and free the corresponding node in the list)
*/

void	ft_unset(t_list	*lst)
{
	t_env	*tmp;
	t_env	*to_free;

	tmp = lst->env;
	to_free = NULL;
	if (lst->cmd[1] == NULL || lst->cmd[2] != NULL)
		return ;
	while (tmp != NULL && ft_strcmp(tmp->next->var, lst->cmd[1]))
	{
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ; //and throw an error or do nothing ?
	else
	{
		if (tmp->next->next != NULL)
		{
			to_free = tmp->next;
			tmp->next = tmp->next->next;
		}
		else
		{
			to_free = tmp->next;
			tmp->next = NULL;
		}
		free(to_free->var);
		free(to_free->value);
		free(to_free);
	}
}
