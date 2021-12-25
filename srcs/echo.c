/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:35 by ysonmez           #+#    #+#             */
/*   Updated: 2021/12/24 16:43:55 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Display message on screen, writes each given STRING to standard output
*	With a space between each and a newline after the last one.
*/

void	ft_echo(t_list	*lst)
{
	int	i;
	int	nl;

	if (lst->cmd[1] == NULL)
		return ;
	if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		i = 2;
		nl = 0;
	}
	else
	{
		i = 1;
		nl = 1;
	}
	while (lst->cmd[i] != NULL)
	{
		if (lst->cmd[i + 1] != NULL)
			printf("%s ", lst->cmd[i]);
		else if (lst->cmd[i + 1] == NULL && nl == 0)
		{
			printf("%s", lst->cmd[i]);
			return ;
		}
		else if (lst->cmd[i + 1] == NULL && nl == 1)
		{
			printf("%s\n", lst->cmd[i]);
			return ;
		}
		i++;
	}
}
