#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		print_msg_exit(ARG_NUM_ERR);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		perror_exit(OPEN_ERR);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (pipex.outfile == -1)
		perror_exit(OPEN_ERR);
	pipex.path = find_path(envp);
	if (!pipex.path)
	{
		free_pipex(&pipex);
		perror_exit(NULL);
	}
	parse_cmd_for_exec(&pipex, argv);
	launch_processes(&pipex, envp);
	free_pipex(&pipex);
	return (0);
}
