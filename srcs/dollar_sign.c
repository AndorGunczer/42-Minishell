# include "../includes/minishell.h"

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
}	t_dollar;

static t_store_env *var_new(char *str, t_test *env)
{
	t_store_env	*new_struct;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isalnum(*(str + i)) == 1)
		i++;
	tmp = ft_substr(str, 0, i);
	new_struct = malloc(sizeof(t_store_env));
	if (new_struct == 0)
		return (0);
	new_struct->string = ft_getenv(tmp, env->env);
	new_struct->var_len = ft_strlen(new_struct->string);
	new_struct->next = NULL;
	return (new_struct);
}

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

char	*path_replace(char *str, t_test *env)
{
	t_dollar re;
	t_store_env *var;
	t_store_env *tmp;
	int x = 0;

	re.len_new = 0;
	re.i = 0;
	re.j = 0;
	while (str[re.i] != '\0')
	{
		if (*(str + re.i) == '$' && *(str + re.i + 1) != '\0' && ft_isalnum(*(str + re.i + 1)) == 1)
		{
			if (0 == x++)
			{
				tmp = var_new(str + re.i + 1, env);
				var = tmp;
				re.len_new += tmp->var_len;
			}
			else
			{
				tmp->next = var_new(str + re.i + 1, env);
				re.len_new += tmp->var_len;
				tmp = tmp->next;
			}
			re.i++;
			while (ft_isalnum(*(str + re.i)) != 0 && *(str + re.i) != '\0')
				re.i++;
		}
		else if (*(str + re.i) != '\0')
		{
			re.len_new++;
			re.i++;
		}
	}
	re.ret = ft_calloc(re.len_new + 1, sizeof(char));
	re.i = 0;
	create_str(str, &re, var);
	return (re.ret);
}