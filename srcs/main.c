/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/06 20:07:37 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner() {
	ft_printf(1, "\033[1;95m ____________________________________________________________\n");
	ft_printf(1, "|  \033[1;96m _    _  _____  _____  _    _ ______ _      _    __   __  \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| |  | ||_   _|/ ____\\| |  | |  ____| |    | |   \\ \\ / /  \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| |  | |  | | | |____ | |__| | |__  | |    | |    \\ V /   \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m| |/\\| |  | |  \\____ \\|  __  |  __| | |    | |     \\ /    \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m|  /\\  |  | |  _____| | |  | | |____| |____| |____ | |    \033[1;35m|\n");
	ft_printf(1, "|  \033[1;96m|_/  \\_|  |_|  \\_____/|_|  |_|______|______|______||_|    \033[1;35m|\n");
	ft_printf(1, "\033[1;95m|____________________________________________________________|\n\n");
	ft_printf(1, "\033[1;95m                       M I N I S H E L L\n\n");
	ft_printf(1, "\033[1;95m                              b y       \n\n");
	ft_printf(1, "\033[1;92m                      rmota-ma & dicosta-       \033[0m\n\n");
}

void	print_tree(t_tree *tree)
{
	if (tree == NULL)
	{
		ft_printf(1, "NULL\n");
		return ;
	}
	ft_printf(1, "Value: [%s]\t Type: [%d]\n", tree->value, tree->type);	
	ft_printf(1, "LEFT: ");
	print_tree(tree->left);
	ft_printf(1, "RIGHT: ");
	print_tree(tree->right);
}

void	free_list(t_token *token)
{
	t_token *temp;
	
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf(1, "Value: [%s]\t Type: [%d]\n", token->value, token->type);	
		token = token->next;
	}
}
int parser(char *line)
{
	if (syntax_check(line) == 0)
		return (0);
	if (expand_check(line))
		line = expand_caller(line);
	t_token *token;
	t_tree	*tree;

	tree = NULL;
	token = assign_token(line);
	printf("TOKEN\n");
	print_tokens(token);
	printf("\n\n");
	if(token)
	{
		pipe_counter(token);
		shell()->tree = tokens_to_tree(token, NULL, tree, 0);
	}
	printf("TREE\n");
	print_tree(shell()->tree);
	free_list(token);
	tree_free(tree);
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	(void)av;
	char *line;
	if (ac != 1)
		return (ft_printf(1, "No arguments are needed\n"), 1);
	print_banner();
	init_shell(ev);
	while(1)
	{
		line = readline("minishell ▸ ");
		if (parser(line) == 0)
			ft_printf(1, "");
		// if(shell()->tree)
		// 	tree_executer();
		// tree_free(shell()->tree);
		// if (!ft_strcmp("exit", line))
		// {
		// 	free(line);
		// 	ft_free_split(shell()->env);
		// 	ft_free_split(shell()->exp);
		// 	exit(0);
		// }
		free(line);
	}
	return (0);
}
