/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:51:24 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:09:14 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	f_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while ((p1[i] || p2[i]))
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] > p2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n && (p1[i] || p2[i]))
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] > p2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	is_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*handle(char  *s)
{
	if (!s)
		return (NULL);
	return (ft_strdup(s));
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	j;
	size_t	len_s1;
	size_t	end;
	size_t	start;

	if (!s1 || !set)
		return (handle(s1));
	len_s1 = ft_strlen(s1);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = len_s1;
	while (end > start && is_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (start < end)
		str[j++] = s1[start++];
	str[j] = '\0';
	return (str);
}
