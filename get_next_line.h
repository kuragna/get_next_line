/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:50:48 by aabourri          #+#    #+#             */
/*   Updated: 2023/02/28 14:35:35 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NETX_LINE_H
# define GET_NETX_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

#ifndef EOL
#define EOL '\n'
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

char	*get_next_line(int fd);
char	*get_line_len(int fd);
#endif
