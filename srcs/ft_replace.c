# include "../includes/minishell.h"

typedef struct s_replace {
	int		i;
	int		j;
	char	*ret;
	int		len_dst;
	int		len_new;
	int		len_src;
}	t_replace;

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

static int	is_same(char *str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == src[j] && str[i] != '\0')
	{
		j++;
		i++;
	}
	if (src[j] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

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
	re.i = 0;
	create_str(str, &re, src, dst);
	return (re.ret);
}

/*	// char	*replace(char *str, char *src, char *dst)
// {
// 	int		len_new;
// 	int		len_src;
// 	int		i;
// 	int		j;
// 	int		len_dst;
// 	char	*ret;

// 	len_new = 0;
// 	len_src = ft_strlen(src);
// 	len_dst = ft_strlen(dst);
// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (is_same((str + i), dst))
// 		{
// 			len_new += len_src;
// 			i += len_dst;
// 		}
// 		else
// 		{
// 			len_new++;
// 			i++;
// 		}
// 	}
// 	ret = ft_calloc(len_new + 1, sizeof(char));
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (is_same((str + i), dst))
// 		{
// 			copy((ret + j), src);
// 			i += len_dst;
// 			j += len_src;
// 		}
// 		else
// 			ret[j++] = str[i++];
// 	}
// 	return (ret);
// }*/