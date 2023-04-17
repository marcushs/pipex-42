/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:17:55 by hleung            #+#    #+#             */
/*   Updated: 2023/04/17 14:37:03 by hleung           ###   ########lyon.fr   */
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
	pipex->fd = NULL;
	pipex->pids = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_b	pipex;
	
	if (argc >= 5)
	{
		init_pipex_b(&pipex);
		pipex.cmd_count = argc - 3;
		pipex.infile = open(argv[1], O_RDONLY);
		if (pipex.infile == -1)
			ft_printf("No such file or directory: %s\n", argv[1]);
		pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		pipex.path = find_path(envp);
		if (!pipex.path)
			free_pipex_exit(&pipex);
		pipex.cmds = args_to_lst(&pipex, argv);
		if (!pipex.cmds)
			free_pipex_exit(&pipex);
		lst_print(pipex.cmds);
		free_pipex(&pipex);
	}
}
