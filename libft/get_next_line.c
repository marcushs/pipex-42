#include "libft.h"

static char	*ft_join_line(char *s1, char *s2, size_t size)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1)
		join = (char *)malloc(size + 1);
	else
		join = (char *)malloc(ft_strlen(s1) + size + 1);
	if (!join)
		return (free(s1), s1 = NULL, NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (j < size)
		join[i++] = s2[j++];
	join[i] = 0;
	return (free(s1), s1 = NULL, join);	
}

static int	ft_check_end_line(char buf[BUFFER_SIZE], char **tmp)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < BUFFER_SIZE && buf[i] && buf[i] != '\n')
		i++;
	if (i < BUFFER_SIZE && buf[i] == '\n')
	{
		i++;
		j++;
	}
	if (i)
	{
		*tmp = ft_join_line(*tmp, buf, i);
		if (!*tmp)
			return (-1);
	}
	while (i < BUFFER_SIZE && j)
		buf[k++] = buf[i++];
	if (j)
		buf[k] = 0;
	return (j);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*tmp;
	int			i;

	tmp = NULL;
	i = ft_check_end_line(buf, &tmp);
	if (i)
		return (tmp);
	else if (i == -1)
		return (NULL);
	while (!i)
	{
		ft_memset(buf, 0, BUFFER_SIZE);
		i = read(fd, buf, BUFFER_SIZE);
		if (i == 0)
			return (tmp);
		else if (i == -1)
			return (free(tmp), tmp = NULL, NULL);
		i = ft_check_end_line(buf, &tmp);
		if (i == -1)
			return (free(tmp), tmp = NULL, NULL);
	}
	return (tmp);
}
