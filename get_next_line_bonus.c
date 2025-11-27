/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdewez <kdewez@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:24:39 by kdewez            #+#    #+#             */
/*   Updated: 2025/11/25 16:24:47 by kdewez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr;

	ptr = s;
	if (!s)
		return (NULL);
	while (*ptr != '\0')
	{
		if (*ptr == (unsigned char)c)
			return ((char *)ptr);
		ptr++;
	}
	if ((unsigned char)c == '\0')
		return ((char *) ptr);
	return (NULL);
}

char	*extract_line(char	*keep)
{
	char	*res;
	int		i;

	i = 0;
	if (!keep || !keep[0])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	if (keep[i] == '\n')
		i++;
	res = ft_substr(keep, 0, i);
	return (res);
}

char	*save_remaining(char *keep)
{
	char	*temp;
	int		i;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	temp = ft_substr (keep, i + 1, ft_strlen(keep) - (i + 1));
	free(keep);
	return (temp);
}

char	*free_all(char *buffer, char **keep)
{
	free(buffer);
	free(keep);
	*keep = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*keep[FD_MAX];
	int			bytes_read;


	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return NULL;
	bytes_read = 1;
	if (!keep[fd])
		keep[fd] = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(keep[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_all(buffer, &keep[fd]));
		buffer[bytes_read] = '\0';
		keep[fd] = ft_strjoin(keep[fd], buffer);
	}
	free(buffer);
	line = extract_line(keep[fd]);
	keep[fd] = save_remaining(keep[fd]);
	return (line);
}

int	main(void)
{
	int	fildes;
	char	*str;

	fildes = open("text.txt", O_RDONLY);
	if(fildes<0)
		return (0);
	str = get_next_line(fildes);
	while(str)
	{
		printf("%s", str);
		str = get_next_line(fildes);
	}

	close(fildes);
	return (0);
}
