/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:08:27 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 12:51:38 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *str, char **envp)
{
	char	*find;
	int		i;
	size_t	len;

	i = 0;
	while (envp[i])
	{
		len = 0;
		while (envp[i][len] != '=')
			len++;
		if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
		{
			find = ft_strchr(envp[i], '=');
			find++;
			if (len == ft_strlen(str))
				return (find);
		}
		i++;
	}
	return (NULL);
}

void	var_to_arg(char *var, t_all *all)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		line_to_arg(&(all->arg[all->count]), var[i]);
		i++;
	}
}

int		check_var_digit(char c, int tmp, int *i)
{
	if (ft_isdigit(c))
	{
		*i = tmp;
		return (1);
	}
	return (0);
}

int		cut_var(char *line, int tmp, int *i, t_all *all)
{
	char	*var;
	char	*var_tmp;
	size_t	len;

	var = NULL;
	if ((ft_strchr(" $;|<>=\"\'", line[tmp])))
	{
		len = (size_t)(tmp - *i - 1);
		tmp = *i;
		var = ft_substr(line, (tmp + 1), len);
		var_tmp = var;
	}
	var = find_var(var, all->env);
	if (var != NULL)
	{
		*i = *i + len;
		if (line[*i + 1] == ' ')
			all->name_parsed = 1;
		var_to_arg(var, all);
		ft_free(&var_tmp);
		return (1);
	}
	ft_free(&var_tmp);
	*i = *i + len;
	return (0);
}

int		check_var(char *line, int *i, char **arg, t_all *all)
{
	int	tmp;

	tmp = *i;
	tmp++;
	all->var = 0;
	if (check_var_digit(line[tmp], tmp, i))
		return (0);
	if ((line[tmp] == ' ') || (line[tmp] == '\0'))
	{
		line_to_arg(arg, line[tmp - 1]);
		all->name_parsed == 0 ? all->name_parsed = 1 : 0;
		return (0);
	}
	while (!(ft_strchr(" $;|<>=\"\'", line[tmp])))
		tmp++;
	if (cut_var(line, tmp, i, all))
		return (1);
	return (0);
}
