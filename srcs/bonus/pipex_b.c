/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:55 by hleung            #+#    #+#             */
/*   Updated: 2023/05/12 10:29:58 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_b.h"

void	init_pipex_b(t_pipex_b *pipex)
{
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->path = NULL;
	pipex->cmds = NULL;
	pipex->cmd_count = 0;
	pipex->hd_idx = 0;
	pipex->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_b	pipex;

	if (argc >= 5)
	{
		init_pipex_b(&pipex);
		pipex.cmd_count = argc - 3;
		if (ft_strcmp(argv[1], "here_doc") == 0)
			launch_heredoc_process(&pipex, argc, argv, envp);
		pipex.infile = open(argv[1], O_RDONLY);
		if (access(argv[1], F_OK) == -1)
			ft_printf("No such file or directory: %s\n", argv[1]);
		else if (access(argv[1], F_OK) == 0 && access(argv[1], R_OK) == -1)
			ft_printf("Cannot open %s: Permission denied\n", argv[1]);
		pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (access(argv[argc - 1], R_OK) == -1)
			ft_printf("Cannot open %s: Permission denied\n", argv[argc - 1]);
		pipex.path = find_path(envp);
		pipex.cmds = args_to_lst(&pipex, argv);
		if (!pipex.cmds)
			free_pipex_exit(&pipex);
		launch_processes(&pipex, envp);
		free_pipex(&pipex);
		return (0);
	}
	return (0);
}
