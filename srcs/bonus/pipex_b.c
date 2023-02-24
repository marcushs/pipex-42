#include "../../includes/pipex_b.h"

t_pipex_b	init_pipex_b()
{
	t_pipex_b	pipex;
	
	pipex.infile = 0;
	pipex.outfile = 0;
	pipex.path = NULL;
	pipex.cmds = NULL;
	pipex.cmds_strs = NULL;
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
		// if (pipex.infile == -1)
		// 	strerror_exit();
		pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		// if (pipex.outfile == -1)
		// 	strerror_exit();
		pipex.path = find_path(envp);
		// if (!pipex.path)
		// {
		// 	free_pipex(&pipex);
		// 	strerror_exit();
		// }
		parse_cmd_for_exec(&pipex, argv, argc);
		for (int i = 0; i < pipex.cmd_count; i++)
			printf("%s\n", pipex.cmds_strs[i]);
		free_pipex(&pipex);
	}
}
