# include "../includes/minishell.h"

static t_words	*ft_wordsnew(void *content)
{
	t_words	*new_struct;

	new_struct = malloc(sizeof(t_words));
	if (new_struct == 0)
		return (0);
	new_struct->word = content;
	new_struct->next = NULL;
	return (new_struct);
}

static int	is_same(char *str, char *src)
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

t_words	*env_create(char **envp)
{
	int		i;
	t_words	*lst;
	t_words	*tmp;

	i = 0;
	while (envp[i])
	{
		if (i == 0)
		{
			tmp = ft_wordsnew(ft_strdup(envp[i]));
			lst = tmp;
		}
		else
		{
			tmp->next = ft_wordsnew(ft_strdup(envp[i]));
			tmp = tmp->next;
		}
		i++;
	}
	return (lst);
}

char	*ft_getenv(char *str, t_words *lst)
{
	int		i;
	char	*cmp;

	i = 0;
	while (str && lst)
	{
		while (lst->word[i] != '=')
		{
			i++;
		}
		cmp = ft_substr(lst->word, 0, i);
		if (is_same(str, cmp) == 1)
		{
			free (cmp);
			return (ft_substr(lst->word, i + 1, ft_strlen(lst->word) - i));
		}
		i = 0;
		free(cmp);
		lst = lst->next;
	}
	return (ft_strdup(""));
}