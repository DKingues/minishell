/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:50:02 by dicosta-          #+#    #+#             */
/*   Updated: 2025/08/04 20:16:34 by rmota-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	print_banner(void)
//{
//	ft_printf(1, "\033[1;95m ________________________________");
//	ft_printf(1, "____________________________\n");
//	ft_printf(1, "|  \033[1;96m _    _  _____  _____  _    _");
//	ft_printf(1, " ______ _      _    __   __  \033[1;35m|\n");
//	ft_printf(1, "|  \033[1;96m| |  | ||_   _|/ ____\\| |  |");
//	ft_printf(1, " |  ____| |    | |   \\ \\ / /  \033[1;35m|\n");
//	ft_printf(1, "|  \033[1;96m| |  | |  | | | |____ | |__| | ");
//	ft_printf(1, "|__  | |    | |    \\ V /   \033[1;35m|\n");
//	ft_printf(1, "|  \033[1;96m| |/\\| |  | |  \\____ ");
//	ft_printf(1, "\\|  __  |  __| | |    | |     \\ /    \033[1;35m|\n");
//	ft_printf(1, "|  \033[1;96m|  /\\  |  | |  _____| | |");
//	ft_printf(1, "  | | |____| |____| |____ | |    \033[1;35m|\n");
//	ft_printf(1, "|  \033[1;96m|_/  \\_|  |_|  \\_____/|_|  ");
//	ft_printf(1, "|_|______|______|______||_|    \033[1;35m|\n");
//	ft_printf(1, "\033[1;95m|____________________________");
//	ft_printf(1, "________________________________|\n\n");
//	ft_printf(1, "\033[1;95m                       M I N I S H E L L\n\n");
//	ft_printf(1, "\033[1;95m                              b y       \n\n");
//	ft_printf(1, "\033[1;92m                      rmota-ma");
//	ft_printf(1, " & dicosta-       \033[0m\n\n");
//}

// void	print_tree(t_tree *tree)
// {
// 	if (tree == NULL)
// 	{
// 		ft_printf(1, "NULL\n");
// 		return ;
// 	}
// 	ft_printf(1, "Value: [%s]\t Type: [%d]\n", tree->value, tree->type);	
// 	ft_printf(1, "LEFT: ");
// 	print_tree(tree->left);
// 	ft_printf(1, "RIGHT: ");
// 	print_tree(tree->right);
// }

// void	print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		ft_printf(1, "Value: [%s]\t Type: [%d]\n", token->value, token->type);	
// 		token = token->next;
// 	}
// }

int	main_line_checks(char *line)
{
	int	acc;
	int	acv;

	acc = 0;
	acv = 0;
	if (!line)
		return (ft_printf(1, "exit\n"), exit_cmd(NULL, 0), 0);
	if (!line[0])
	{
		shell()->exit = 0;
		return (free(line), 0);
	}
	while (line[acc])
	{
		if (!ft_isspace(line[acc]))
			break ;
		acc++;
	}
	while (line[acv] && line[acv] != '\n')
		acv++;
	if (acv == acc)
		return (0);
	return (1);
}

int	main_tree_parser(void)
{
	if (manage_here_doc() == 1)
	{
		return (0);
	}
	if (shell()->tree->type == PIPE)
	{
		shell()->pid = fork();
		if (!shell()->pid)
		{
			choose_signal(CHLD);
			tree_executer(0, 0, NULL, NULL);
		}
		else
		{
			choose_signal(IGNORE);
			waitpid(shell()->pid, &shell()->exit, 0);
			choose_signal(ROOT);
			shell()->exit = shell()->exit / 256;
		}
	}
	else
		nptree_executer(NULL, NULL, 0);
	return (1);
}

void	reset_input(char *line)
{
	close_fds();
	shell()->pid = 0;
	shell()->in = dup(0);
	shell()->out = dup(1);
	tree_free(shell()->tree);
	if (shell()->docs)
		free(shell()->docs);
	shell()->docs = NULL;
	shell()->tree = NULL;
	shell()->count = 0;
	shell()->pipe_count = 0;
	shell()->hist = hist_manage(line, 0);
	if (!shell()->hist)
	{
		shell()->exit = 1;
		exit_cmd(NULL, 0);
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (ft_printf(2, "No arguments are needed\n"), 1);
	init_shell(ev);
	while (1)
	{
		choose_signal(ROOT);
		line = readline("minishell ▸ ");
		if (!main_line_checks(line))
			continue ;
		reset_input(line);
		if (!parser(line))
			continue ;
		if (shell()->tree)
		{
			if (!main_tree_parser())
				continue ;
		}
		else
			shell()->exit = 0;
	}
	return (0);
}
