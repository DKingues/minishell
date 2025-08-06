/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:57:26 by dicosta-          #+#    #+#             */
/*   Updated: 2025/07/26 17:36:04 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dequote_tokens(t_token **token)
{
	if (!token || !*token)
		return ;
	while ((*token)->next)
	{
		if (count_quotes((*token)->value) % 2 == 0)
			(*token)->value = remove_quotes((*token)->value, 0, NULL);
		(*token) = (*token)->next;
	}
	if (count_quotes((*token)->value) % 2 == 0)
		(*token)->value = remove_quotes((*token)->value, 0, NULL);
	while ((*token)->prev)
		(*token) = (*token)->prev;
}

t_token	*assign_token(char *line)
{
	t_token	*token;
	char	**tokens;
	int		i;
	int		token_type;

	token = NULL;
	tokens = split_tokens(line);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != 0)
		{
			token_type = get_token_type(tokens[i]);
			if ((token_type == READ || token_type == HD
					|| token_type == TRUNCATE || token_type == APPEND)
				&& get_token_type(tokens[i + 1]) != PIPE)
				token = append_node(token, tokens[++i], token_type);
			else
				token = append_node(token, tokens[i], token_type);
		}
		i++;
	}
	dequote_tokens(&token);
	ft_free_split(tokens);
	return (token);
}

/*t_token	*remove_redir(t_token *token)
{
	t_token	*temp;
	t_token	*next;
	
	temp = token;
	while (temp)
	{
		next = temp->next;
		if (temp->type == READ || temp->type == HERE_DOC
		|| temp->type == TRUNCATE || temp->type == APPEND)
		{
			temp->next->type = temp->type;
			if (temp->prev)
			{
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
			}
			else
				temp->next->prev = NULL;
			free(temp);
		}
		temp = next;
	}
	return (temp);
}*/

int	get_token_type(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (PIPE);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (HD);
		else if (input[i] == '<')
			return (READ);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (APPEND);
		else if (input[i] == '>')
			return (TRUNCATE);
		else
			return (ARG);
	}
	return (1);
}

void	else_exec(char *path)
{
	char	*temp;

	temp = ft_nfstrjoin("minishell: ", path);
	if (!temp)
	{
		ft_printf(2, "minishell: malloc error\n");
		ft_free_split(shell()->env);
		exit(1);
	}
	perror(temp);
	free(temp);
	shell()->exit = 127;
}
