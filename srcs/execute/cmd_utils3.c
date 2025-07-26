/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:52:38 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/07/26 17:45:00 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_blank(char *msg)
{
	int		var;
	char	*temp;

	var = 0;
	while (msg[var] != ' ')
		var++;
	temp = ft_calloc(sizeof(char), var + 1);
	if (!temp)
		return (NULL);
	var = 0;
	while (msg[var] != ' ')
	{
		temp[var] = msg[var];
		var++;
	}
	return (temp);
}

char	**quoting_set(int var)
{
	char	**temp;

	while (shell()->exp[var])
		var++;
	temp = ft_calloc(sizeof(char *), var + 1);
	if (!temp)
		malloc_err(NULL, "malloc");
	var = 0;
	while (shell()->exp[var])
	{
		if (shell()->exp[var][exp_len(shell()->exp[var])] == '=')
		{
			temp[var] = exp_strdup(shell()->exp[var]);
			if (!temp[var])
				malloc_err(temp, "malloc");
		}
		else
		{
			temp[var] = ft_strdup(shell()->exp[var]);
			if (!temp[var])
				malloc_err(temp, "malloc");
		}
		var++;
	}
	return (ft_free_split(shell()->exp), temp);
}

char	*exp_strdup(const char *s1)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	len = exp_len(s1);
	tmp = ft_calloc(sizeof(char), ft_strlen(s1) + 4);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = s1[i];
	i++;
	tmp[i] = 34;
	i++;
	while (i < sizeof(char) * (ft_strlen(s1) + 1))
	{
		tmp[i] = s1[i - 1];
		i++;
	}
	tmp[i] = 34;
	return (tmp);
}

int	error_syntax(char *array)
{
	int	i;

	i = 0;
	if (array[i] == '\0')
		return (i);
	while (array[i] != '\0')
	{
		if ((array[i] >= '0' && array[i] <= '9')
			|| (array[i] == '-' || array[i] == '+') || ft_isspace(array[i]))
		{
			if ((array[i] == '-' || array[i] == '+')
				&& ((array[i + 1] < '0' || array[i + 1] > '9')
					|| (i != '\0')))
			{
				if (!ft_isspace(array[i]))
					return (0);
			}
		}
		else
			return (0);
		i++;
	}
	return (i);
}

int	long_check(char *str)
{
	int					a;
	unsigned long long	res;
	long long			count;

	a = 0;
	res = 0;
	count = 1;
	if ((str[a] == '-' || str[a] == '+'))
	{
		if (str[a] == '-')
			count *= -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		res = res * 10 + (str[a] - '0');
		if (res > LONG_MAX)
			return (1);
		a++;
	}
	return (0);
}
