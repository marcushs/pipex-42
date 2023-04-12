#include "../../includes/pipex.h"

t_pipex	init_pipex(void)
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
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	pipex.path = find_path(envp);
	parse_cmd_for_exec(&pipex, argv);
	launch_processes(&pipex, envp);
	free_pipex(&pipex);
	return (0);
}
