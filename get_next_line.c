#include "get_next_line.h"
#include <string.h>

void	find_leaks()
{
	system("leaks -q main");
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		len_s1 = 0;
	else
		len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	memmove(str, s1, len_s1);
	memmove(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	return (str);
}

char	*get_line_buff(char **ptr)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if ((*ptr) == NULL || *(*ptr) == '\0')
		return (NULL);
	while ((*ptr)[i] != '\n' && (*ptr)[i] != '\0')
		i++;
	if ((*ptr)[i] == '\0')
		i++;
	else
		i += 2;
	line = (char*)malloc(sizeof(char) * i);
	if (!line)
		return (NULL);
	while (++j < (i - 1))
		line[j] = *(*ptr)++;
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char buff_read[BUFFER_SIZE + 1];
	char *line;
	int nbyte;

	if (fd < 0 || fd >= 1000 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buff_read, BUFFER_SIZE);
		if (nbyte > 0)	
		{
			buff_read[nbyte] = '\0';
			buffer = ft_strjoin(buffer, buff_read);
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
	printf("%s", get_next_line(4));
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
