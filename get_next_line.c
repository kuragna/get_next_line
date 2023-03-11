/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:01:41 by aabourri          #+#    #+#             */
/*   Updated: 2023/03/11 20:36:17 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

char	*get_line_(char **buffer)
{
	char	*line;
	char	*tmp;
	char	*null;
	size_t	i;

	null = NULL;
	if (!*buffer || !**buffer)
		return (get_freed(buffer, &null));
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	if ((*buffer)[i] != '\0')
		i++;
	tmp = *buffer;
	line = ft_substr(*buffer, 0, i);
	*buffer = ft_substr(*buffer, i, ft_strlen(*buffer + i));
	free(tmp);
	tmp = NULL;
	return (line);
}

char	*get_join(char *s1, char *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		len_s1 = 0;
	}
	else
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s2 + len_s1] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buff_read;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	buff_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (nbyte > 0)
	{
		nbyte = read(fd, buff_read, BUFFER_SIZE);
		if (nbyte == -1)
			return (get_freed(&buffer, &buff_read));
		if (nbyte > 0)
		{
			buff_read[nbyte] = '\0';
			buffer = get_join(buffer, buff_read);
			if (!buffer)
				return (get_freed(&buffer, &buff_read));
			if (ft_strchr(buffer, '\n'))
				break ;
		}
	}
	free(buff_read);
	return (get_line_(&buffer));
}
#if 1
void	find_leaks()
{
	system("leaks -q main");
}
int main()
{
	atexit(find_leaks);
	int fd = open("input.txt", O_RDONLY);
	if (fd < 0)
		printf("ERROR: could not open the file.");
	char	*s;
	while ((s = get_next_line(fd)))
	{
		printf("%s", s);
		free(s);
	}
	int i = 0;
	while (i < 10)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
	return 0;
}
#endif

char	*get_freed(char **p1, char **p2)
{
	if (*p1 != NULL)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (*p2 != NULL)
	{
		free(*p2);
		*p2 = NULL;
	}
	return (NULL);
}
