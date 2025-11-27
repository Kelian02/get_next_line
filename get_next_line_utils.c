/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdewez <kdewez@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:36:28 by kdewez            #+#    #+#             */
/*   Updated: 2025/11/25 13:08:15 by kdewez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*answer;

	i = 0;
	answer = (char *)malloc(ft_strlen(s1) + 1);
	if (!answer)
		return (NULL);
	while (s1[i])
	{
		answer[i] = s1[i];
		i++;
	}
	answer[i] = '\0';
	return (answer);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t		i;
	size_t		s1length;
	char		*answer;

	i = 0;
	answer = malloc(ft_strlen(s2) + ft_strlen(s1) + 1);
	if (!answer)
		return (NULL);
	while (s1 && s1[i])
	{
		answer[i] = s1[i];
		i++;
	}
	i = 0;
	s1length = ft_strlen(s1);
	free(s1);
	while (s2 && s2[i])
	{
		answer[i + s1length] = s2[i];
		i++;
	}
	answer[i + s1length] = '\0';
	return (answer);
}

static char	*set_answer(char *answer)
{
	answer = malloc(1);
	if (!answer)
		return (NULL);
	answer[0] = '\0';
	return (answer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*answer;
	size_t			i;
	unsigned int	slength;

	slength = ft_strlen(s);
	i = 0;
	answer = NULL;
	if (start > slength)
		return (set_answer(answer));
	if (len > slength - start)
		answer = malloc(slength - start + 1);
	else
		answer = malloc(len + 1);
	if (!answer)
		return (NULL);
	while (i < len && s[i + start])
	{
		answer[i] = s[i + start];
		i++;
	}
	answer[i] = '\0';
	return (answer);
}
