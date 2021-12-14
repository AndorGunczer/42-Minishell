// int		arrlen(char **arr)
// {
// 	int i;

// 	i = 0;
// 	while(arr && arr[i][0] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	pwd(t_test *lst)
// {
// 	char *str;

// 	if (arrlen(lst->cmd) == 1)
// 	{
// 		str = ft_getenv("PWD");
// 		if (str)
// 		{
// 			ft_putendl_fd(str);
// 			free(str);
// 		}
// 	}
// }