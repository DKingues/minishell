/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:06 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/19 17:10:16 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
echo " ' $USER lives at $HOME"
Count how many "$" are in command
*/
int		expand_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quotes(line, i)) 
		{
			i++;
			i += skip_quotes(&line[i], '\'');	
		}
		else if (line[i] == '$')
			return (1);
		i++;
	}
	return(0);
}
char	*expand_caller(char *line)
{
	int	i;
	char *expansion;
	char *expanded_line;

	i = 0;
	expanded_line = ft_strdup(line);
	while (expanded_line[i])
	{
		if (expanded_line[i] == '\'' && !in_double_quotes(expanded_line, i)) 
		{
			i++;
			i += skip_quotes(&expanded_line[i], '\'');	
		}
		else if (expanded_line[i] == '$')
		{
			expansion = get_expansion(&expanded_line[i]); // expansion = dicosta- expanded_line = echo " ' -dicosta lives at $HOME"
			expanded_line = remove_expansion(expanded_line);
			if (expansion)
				expanded_line = add_expansion(expanded_line, expansion, i);
		}
		i++;
	}
	return (expanded_line);
}

int	expansion_len(char *line)
{
	int	i;
	int	j;
	
	j = 0;
	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	while (line[i] && (ft_isalnum(line[i])))
	{
		j++;
		i++;
	}
	return (j);
}

char	*add_expansion(char *line, char *expansion, int i)
{
	int 	j;
	int		k;
	int		l;
	int 	full_len;
	char	*expanded_line;

	j = 0;
	k = 0;
	l = 0;
	full_len = ft_strlen(line) + ft_strlen(expansion);
	expanded_line = ft_calloc(sizeof(char), full_len + 1);
	if (!expanded_line)
		return (free(expanded_line), NULL);
	while (j < full_len)
	{
		if (j == i)
		{
			while (expansion[k])
				expanded_line[j++] = expansion[k++];
		}
		expanded_line[j++] = line[l++];
	}
	return (free(line), free(expansion), expanded_line);
}

char	*get_expansion(char *line)
{
	int	i;
	int len;
	char *arg;
	char *expansion;
	
	i = 0;
	len = arg_len(line);
	arg = ft_calloc(sizeof(char), len + 1);
	if (!arg)
		return (free(arg), NULL);
	while (i < len)
	{
		arg[i] = line[i];
		i++;
	}
	expansion = expand_arg(arg);
	return (expansion);
}


