#include "get_next_line.h"
#include <string.h>

void	find_leaks()
{
	system("leaks main");
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = "";
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

char	*get_line_buff(char *str)
{
	char	*line;
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != EOL && str[i] != '\0')
		i++;
	line = (char*)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j < (i + 1) && str[j] != '\0')
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while ((*s != '\0') && (*s != c))
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char buff_read[BUFFER_SIZE + 1];
	char *line;
	int nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buff_read, BUFFER_SIZE);
		/*if (nbyte == -1)
			return (NULL);*/
		if (nbyte != 0)	
		{
			buff_read[nbyte] = '\0';
			buffer = ft_strjoin(buffer, buff_read);
		}
	}
	line = get_line_buff(buffer);
	buffer = ft_strchr(buffer, '\n') + 1;
	return (line);
}

/*int main()
{
	atexit(find_leaks);
	int fd = open("input.txt", O_RDONLY);
	if (fd < 0)
		printf("ERROR: could not open the file.");
	printf("%s", get_next_line(fd));
	close(fd);
	return 0;
}*/

/*int main2()
{
	atexit(find_leaks);
	char	*buff = "abc\n123\n321\ncba";
	get_new_buff(buff);
	return 0;
}*/
