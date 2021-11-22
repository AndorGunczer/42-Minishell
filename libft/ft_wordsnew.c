#include "libft.h"

t_words	*ft_wordsnew(void *content)
{
	t_words	*new_struct;

	new_struct = malloc(sizeof(t_words));
	if (new_struct == 0)
		return (0);
	new_struct->word = content;
	new_struct->next = NULL;
	return (new_struct);
}

void	ft_create_words(t_words **lst, char *words)
{
	char	**str;
	t_words	*temp;

	str = ft_split(words, ' ');
	temp = ft_wordsnew(*str);
	*lst = temp;
	str++;
	while (*str != '\0')
	{
		(temp)->next = ft_wordsnew(*str);
		(temp) = (temp)->next;
		str++;
	}
}

t_list	*ft_lstnew(int prefix, int suffix, char *words)
{
	t_list	*new_struct;

	new_struct = malloc(sizeof(t_list));
	if (new_struct == 0)
		return (0);
	new_struct->prefix = prefix;
	new_struct->suffix = suffix;
	ft_create_words(&new_struct->words, words);
	new_struct->next = NULL;
	return (new_struct);
}
