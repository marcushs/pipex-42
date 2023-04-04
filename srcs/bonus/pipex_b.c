#include "../../includes/pipex_b.h"

t_pipex_b	init_pipex_b()
{
	t_pipex_b	pipex;
	
	pipex.infile = 0;
	pipex.outfile = 0;
	pipex.path = NULL;
	pipex.cmds = NULL;
	pipex.cmd_count = 0;
	pipex.hd_idx = 0;
	pipex.fds = NULL;
	pipex.pids = NULL;
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_b	pipex;
	
	if (argc >= 5)
	{
		pipex = init_pipex_b();
		pipex.cmd_count = argc - 3;
		pipex.infile = open(argv[1], O_RDONLY);
		pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		pipex.path = find_path(envp);
		// if (!pipex.path)
		// {
		// 	free_pipex(&pipex);
		// 	strerror_exit();
		// }
		pipex.cmds = args_to_lst(&pipex, argv);
		//if (!pipex.cmds)
		// for (int i = 0; i < pipex.cmd_count; i++)
		// {
		// 	for (int j = 0; pipex.cmds->cmd_strs[i][j]; j++)
		// 		printf("%s ", pipex.cmds->cmd_strs[i][j]);
		// 	printf("\n");
		// }

		//free_2d_arr(pipex.cmds_strs);
		free_pipex(&pipex);
	}
}
