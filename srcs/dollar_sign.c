/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:43:33 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:43:36 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_store_env {
	char	*string;
	int		var_len;
	struct s_store_env *next;
} t_store_env;

typedef struct s_dollar {
	int		i;
	int		j;
	char	*ret;
	int		len_dst;
	int		len_new;
	int		len_src;
	int		x;
	t_store_env	*var;
	t_store_env *tmp;
}	t_dollar;

/*	creates a new t_store_env list */

static t_store_env *var_new(char *str, t_list *lst)
{
	t_store_env	*new_struct;
	char		*tmp;
	int			i;

	i = 0;
	while (ft_isalnum(*(str + i)) == 1)
		i++;
	tmp = ft_substr(str, 0, i);
	new_struct = malloc(sizeof(t_store_env));
	if (new_struct == 0)
		return (0);
	new_struct->string = ft_getenv(tmp, lst->env);
	new_struct->var_len = ft_strlen(new_struct->string);
	new_struct->next = NULL;
	return (new_struct);
}

/*	Copies character of dst at the given index to
*	character of str at the given index
*/

static void	copy(char *str, char *dst)
{
	int i;
	int j;
	int	len = ft_strlen(dst);

	i = 0;
	j = 0;
	while (i < len)
	{
		str[i++] = dst[j++];
	}
}

/*	Recreates the *str by replacing env names with their values
*	based on the contents of the *var list.
*/

static void	create_str(char *str, t_dollar *re, t_store_env *var)
{
	while (str[re->i] != '\0')
	{
		if (*(str + re->i) == '$' && ft_isalnum(*(str + re->i + 1)) == 1)
		{
			copy((re->ret + re->j), var->string);
			re->i++;
			while (ft_isalnum(*(str + re->i)) != 0)
				re->i++;
			re->j += var->var_len;
			var = var->next;
		}
		else
			re->ret[re->j++] = str[re->i++];
	}
}

/*	Different pairs in env have different amount of characters
*	thus we create a list to store the env value and the length
*	of the env value.
*/

static void	create_lst(char *str, t_dollar *re, t_list *lst)
{
	while (str[re->i] != '\0')
	{
		if (*(str + re->i) == '$' &&
			*(str + re->i + 1) != '\0' && ft_isalnum(*(str + re->i + 1)) == 1)
		{
			if (0 == re->x++)
			{
				re->tmp = var_new(str + re->i++ + 1, lst);
				re->var = re->tmp;
			}
			else
			{
				re->tmp->next = var_new(str + re->i++ + 1, lst);
				re->tmp = re->tmp->next;
			}
			re->len_new += re->tmp->var_len;
			while (ft_isalnum(*(str + re->i)) != 0 &&
				*(str + re->i) != '\0' && *(str + re->i) != '$')
				re->i++;
		}
		else if (*(str + re->i) != '\0')
		{
			re->len_new++;
			re->i++;
		}
	}
}

/*	Detects environment variable name in *str
*	and replaces that name with the environment value.
*/

char	*path_replace(char *str, t_list *lst)
{
	t_dollar re;

	re.x = 0;
	re.len_new = 0;
	re.i = 0;
	re.j = 0;
	create_lst(str, &re, lst);
	re.ret = ft_calloc(re.len_new + 1, sizeof(char));
	re.ret[re.len_new] = '\0';
	re.i = 0;
	create_str(str, &re, re.var);
	if (str)
		free(str);
	// ft_lstclear()
	return (re.ret);
}