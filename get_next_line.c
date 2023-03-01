/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:45:42 by aabourri          #+#    #+#             */
/*   Updated: 2023/03/01 13:26:01 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	len = strlen(s1);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = (char*)ft_strdup("");
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


char	*get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != EOL && str[i] != '\0')
		i++;
	line = (char*)malloc(sizeof(char) + (i + 2));
	memcpy(line, str, i);
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char buff[BUFFER_SIZE + 1];
	char *line;
	int nbyte;
	static char	*string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buff, BUFFER_SIZE);
		buff[nbyte] = '\0';
		string = ft_strjoin(string, buff);
	}
	line = get_line(string);
	string += strlen(line);
	return (line);
}

int main()
{
	int fd = open("input.txt", O_RDONLY);
	if (fd == -1)
		printf("Could not open the file\n");
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}
