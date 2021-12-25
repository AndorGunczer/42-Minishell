/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:38 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:44:19 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Print the environment */

void	ft_env(t_list	*lst)
{
	t_env	*tmp;

	tmp = lst->env;
	if (lst->cmd[1] != NULL)
		return ; // throw error or just ignore ?
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}
