/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:42:59 by hleung            #+#    #+#             */
/*   Updated: 2023/04/18 15:11:15 by hleung           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	*get_fd(void)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
	{
		perror("Malloc error");
		return (NULL);
	}
	if (pipe(fd) == -1)
	{
		perror("Error opening pipe");
		return (NULL);
	}
	return (fd);
}

void	start_heredoc(void)
{
	int	*fd;

	fd = get_fd();
	
}