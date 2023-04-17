/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:55:51 by hleung            #+#    #+#             */
/*   Updated: 2023/04/17 14:03:22 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static t_pipex	init_pipex(void)
{
	t_pipex	pipex;

	pipex.infile = 0;
	pipex.outfile = 0;
	pipex.path = NULL;
	pipex.cmd1_strs = NULL;
	pipex.cmd2_strs = NULL;
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
	pipex.fd = NULL;
	pipex.pid1 = 0;
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		print_msg_exit(ARG_NUM_ERR);
	pipex = init_pipex();
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		ft_printf("No such file or directory: %s\n", argv[1]);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (pipex.outfile && access(argv[argc - 1], R_OK) == -1)
		ft_printf("Cannot open %s: Permission denied\n", argv[argc - 1]);
	pipex.path = find_path(envp);
	parse_cmd_for_exec(&pipex, argv);
	launch_processes(&pipex, envp);
	free_pipex(&pipex);
	return (0);
}
