#include "get_next_line.h"
#include <string.h>

void	*ft_realloc(void *ptr, size_t new_size);

void	find_leaks()
{
	system("leaks -q main");
}



char	*ft_strjoin(char *s1, char const *s2, char	**tmp)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		len_s1 = 0;
	else
		len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	str = (char*)malloc(sizeof(char) * len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	memmove(str, s1, len_s1);
	memmove(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	*tmp = str;
	return (str);
}

char	*get_line_buff(char **buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!*buffer || !**buffer)
		return (NULL);
	while ((*buffer)[i] != EOL && (*buffer)[i])
		i++;
	if (!(*buffer)[i])
		i++;
	else
		i += 2;
	line = (char*)malloc(sizeof(char) * i);
	if (!line)
		return (NULL);
	while (++j < (i - 1))
		line[j] = (*(*buffer)++);
	line[j] = '\0';
	return (line);
}

void	get_freed(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char buff_read[BUFFER_SIZE + 1];
	int nbyte;
	char	*tmp;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buff_read, BUFFER_SIZE);
		if (nbyte > 0)	
		{
			buff_read[nbyte] = '\0';
			buffer = ft_strjoin(buffer, buff_read, &tmp);
			get_freed(tmp);
			if (strchr(buffer, EOL))
                break ;
        }
	}
	line = get_line_buff(&buffer);
	return (line);
}
#if 0
int main()
{
	atexit(find_leaks);
	int fd = open("input.txt", O_RDONLY);
	if (fd < 0)
		printf("ERROR: could not open the file.");
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return 0;
}
#endif
#if 0
int main()
{
	atexit(find_leaks);
	char	*buff = "abc\n123\n321\ncba";
	char	*line;
	line = get_line_buff(buff);
	printf("{line = %s}\n", line);
	return 0;
}
#endif

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!new_size || !ptr)
		return (NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	memmove(new_ptr, ptr, new_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}
