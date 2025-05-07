/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorpot <scorpot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:07:04 by scorpot           #+#    #+#             */
/*   Updated: 2025/05/04 17:39:54 by scorpot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	multiple_pipes(int count, char **args, char **envp)
// {
// 	int	*pids;
// 	int	proc;
// 	int	code;
// 	int	fd[2];

// 	code = 0;
// 	if (pipe(fd) == -1)
// 		error();
// 	pids = ft_calloc(sizeof(int), count + 1);
// 	pids[0] = fork();
// 	if (pids[0] < 0)
// 		error();
// 	if (pids[0] == 0)
// 		first_process(args, envp, fd);
// 	else
// 		dup2(fd[0], 0);
// 	close(fd[1]);
// 	proc = parent(count, args, envp, pids);
// 	close_fds();
// 	close(0);
// 	waitpid(pids[0], NULL, 0);
// 	waitpids(pids, count);
// 	waitpid(proc, &shell()->exit, 0);
// 	shell()->exit /= 256;
// 	return (0);
// }

// void	error(void)
// {
// 	perror("Error");
// 	close_fds();
// 	exit(1);
// }