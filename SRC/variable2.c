/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:27:22 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 17:58:51 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_to_arg2(char *var, t_all *all)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		while (ft_isspace(var[i]))
			space_skip(all, &i);
		check_arg(all);
		line_to_arg(&(all->arg[all->count]), var[i]);
		if (all->name_parsed == 0 || all->name_parsed == 2)
			all->name_parsed = 1;
		i++;
	}
}

int		cut_var2(char *line, int tmp, int *i, t_all *all)
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
		var_to_arg2(var, all);
		ft_free(&var_tmp);
		return (1);
	}
	ft_free(&var_tmp);
	*i = *i + len;
	return (0);
}

int		check_var2(char *line, int *i, char **arg, t_all *all)
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
	if (cut_var2(line, tmp, i, all))
		return (1);
	return (0);
}
