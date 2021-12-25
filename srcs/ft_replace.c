/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:45:22 by home              #+#    #+#             */
/*   Updated: 2021/12/24 16:45:24 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_replace {
	int		i;
	int		j;
	char	*ret;
	int		len_dst;
	int		len_new;
	int		len_src;
}	t_replace;

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

/*	Recreates the *str by replacing every instance of
*	*dst by *src
*/

static void	create_str(char *str, t_replace *re, char *src, char *dst)
{
	while (str[re->i] != '\0')
	{
		if (is_same((str + re->i), dst))
		{
			copy((re->ret + re->j), src);
			re->i += re->len_dst;
			re->j += re->len_src;
		}
		else
			re->ret[re->j++] = str[re->i++];
	}
}

/*	Function that replaces every instance of *dst
*	to *src in the given *str
*/

char	*replace(char *str, char *src, char *dst)
{
	t_replace re;

	re.len_new = 0;
	re.len_src = ft_strlen(src);
	re.len_dst = ft_strlen(dst);
	re.i = 0;
	re.j = 0;
	while (str[re.i] != '\0')
	{
		if (is_same((str + re.i), dst))
		{
			re.len_new += re.len_src;
			re.i += re.len_dst;
		}
		else
		{
			re.len_new++;
			re.i++;
		}
	}
	re.ret = ft_calloc(re.len_new + 1, sizeof(char));
	re.ret[re.len_new] = '\0';
	re.i = 0;
	create_str(str, &re, src, dst);
	if (str)
		free(str);
	return (re.ret);
}
