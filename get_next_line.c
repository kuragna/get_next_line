/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:01:41 by aabourri          #+#    #+#             */
/*   Updated: 2023/03/08 18:29:03 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	find_leaks(void)
{
	system("leaks -q main");
}

char	*get_line_(char **buffer)
{
	char	*line;
	char	*tmp;
	size_t	i;

	if (!*buffer || !**buffer)
		return (free(*buffer), NULL);
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

char	*get_join(char *s1, char const *s2)
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
	str = malloc(sizeof *str * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s2 + len_s1] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

char	*get_freed(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		buff_read[BUFFER_SIZE + 1];
	int			nbyte;

	if (fd < 0  || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0)
	{
		nbyte = read(fd, buff_read, BUFFER_SIZE);
		if (nbyte == -1)
			return (free(buffer), NULL);
		if (nbyte > 0)
		{
			buff_read[nbyte] = '\0';
			buffer = get_join(buffer, buff_read);
			if (ft_strchr(buffer, '\n'))
				break ;
		}
	}

	return (get_line_(&buffer));
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
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return 0;
}
#endif

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		len = 0;
	if (len_s < len)
		len = len_s - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((char *)dst + i) = *((char *)src + i);
		i++;
	}
	return (dst);
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