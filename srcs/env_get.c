/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:02 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:44:09 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Checks if *str and *src match */

int	is_same(char *str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == src[j] && str[i] != '\0' && str[j] != '\0')
	{
		j++;
		i++;
	}
	if (src[j] == str[i] || (src[j] == '\0' && str[i] == '\0'))
		return (TRUE);
	else
		return (FALSE);
}

/*	Takes *str, and tries it against the names of the env
*	if *str == env[i] -> TRUE, returns the value of the env[i]
*	if FALSE, returns an empty string
*/

char	*ft_getenv(char *str, t_env *lst)
{
	while (str && lst)
	{
		if (is_same(str, lst->var) == 1)
			return (ft_substr(lst->value, 0, ft_strlen(lst->value)));
		lst = lst->next;
	}
	return (ft_strdup(""));
}
