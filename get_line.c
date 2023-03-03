#include <stdlib.h>

char	*get_line(char **ptr)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (*(*ptr) == '\0')
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