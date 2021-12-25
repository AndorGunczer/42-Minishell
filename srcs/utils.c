/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:45:52 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:50:45 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Check if the string contains one of the shell's operator
*		if not, return 0
*/

int	is_opt(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, ">>") == 0)
		return (3);
	else if (ft_strcmp(str, "<") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (5);
	else
		return (0);

}

/*	Compare two strings */

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0'&& s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char) s2[i]);
}

/* Can be useful later */
int		count_str(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (-1);
	while(arr[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	**ncpy_str(char **arr, int n)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (n + 2));
	if (new == NULL)
		return (NULL);
	while (i <= n)
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
/* */

//to norm
char	**space_fix(char **arr)
{
	char	**new;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
			count++;
		else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
			count++;
		if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
			count++;
		else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
			count++;
		i++;
	}
	i = 0;
	j = 0;
	if (count == 0)
		return (arr);
	new = (char **)malloc(sizeof(char *) * (count_str(arr) + count + 1));
	while (arr[i] != NULL)
	{
		if (arr[i][0] == '<' || arr[i][0] == '>')
		{
			if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
				new[j] = ft_strdup("<");
			else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
				new[j] = ft_strdup("<<");
			else if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
				new[j] = ft_strdup(">");
			else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
				new[j] = ft_strdup(">>");
			j++;
			if (arr[i][0] == '<' && ft_isalnum(arr[i][1]))
				new[j] = ft_strdup(&arr[i][1]);
			else if (arr[i][0] == '<' && arr[i][1] == '<' && ft_isalnum(arr[i][2]))
				new[j] = ft_strdup(&arr[i][2]);
			else if (arr[i][0] == '>' && ft_isalnum(arr[i][1]))
				new[j] = ft_strdup(&arr[i][1]);
			else if (arr[i][0] == '>' && arr[i][1] == '>' && ft_isalnum(arr[i][2]))
				new[j] = ft_strdup(&arr[i][2]);
		}
		else
			new[j] = ft_strdup(arr[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	ft_memfreeall((void **)arr);
	return (new);
}
