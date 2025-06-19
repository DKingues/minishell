/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/06/19 17:43:23 by dicosta-         ###   ########.fr       */
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
	char *str;
	str = NULL;
	if (syntax_check(line) == 0)
		return (0);
	if (expand_check(line))
		str = expand_caller(line);
	t_token *token;
	t_tree	*tree;

	tree = NULL;
	if (str)
	{
		token = assign_token(str);
		free(str);
	}
	else
	{
		token = assign_token(line);
	}
	/* printf("TOKEN\n");
	print_tokens(token);
	printf("\n\n"); */
	if(token)
	{
		pipe_counter(token);
		shell()->tree = tokens_to_tree(token, NULL, tree, 0);
	}
/* 	printf("TREE\n");
	print_tree(shell()->tree); */
	free_list(token);
	//tree_free(tree);
	return (1);
}

void	reset_input(char *line)
{
	//printf("%s\n", line);
	if(shell()->tree)
	{
		tree_free(shell()->tree);
		shell()->tree = NULL;
	}
	if(shell()->docs)
		free(shell()->docs);
	shell()->count = 0;
	shell()->pipe_count = 0;
	shell()->hist = hist_manage(line, 0);
}

int	main(int ac, char **av, char **ev)
{
	(void)av;
	char *line;
	//char *str;
	int	pid;
	
	if (ac != 1)
		return (ft_printf(1, "No arguments are needed\n"), 1);
	//print_banner();
	init_shell(ev);
	while(1)
	{
		line = readline("minishell ▸ ");
		reset_input(line);
		//str = ft_strdup(line);
		if (parser(line) == 0)
			ft_printf(1, "");
		if(shell()->tree)
		{
			manage_here_doc();
			if(shell()->tree->type == PIPE)
			{
				pid = fork();
				if(!pid)
					tree_executer();
				else
					waitpid(pid, NULL, 0);
			}
			else
				nptree_executer();
		}
		free(line);
		//free(str);
	}
	return (0);
}
