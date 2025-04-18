/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:55:11 by azaimi            #+#    #+#             */
/*   Updated: 2025/04/11 00:09:00 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strjoin_char(char *s1, char c)
{
	int		len;
	char	*ptr;
	char	*dst;

	if (!s1)
	{
		dst = (char *)malloc(2 * sizeof(char));
		if (!dst)
			return (NULL);
		dst[0] = c;
		dst[1] = '\0';
		return (dst);
	}
	len = ft_strlen(s1) + 1;
	dst = (char *)malloc((len + 1) * sizeof(char));
	ptr = dst;
	if (!dst)
		return (NULL);
	while (*s1)
		*dst++ = *s1++;
	*dst++ = c;
	*dst = '\0';
	return (ptr);
}

char	*ft_strcpy(char *src, char *dst)
{
	while (*src)
		*dst++ = *src++;
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*ptr;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc((len + 1) * sizeof(char));
	ptr = dst;
	if (!dst)
		return (NULL);
	if (s1)
		dst = ft_strcpy(s1, dst);
	if (s2)
		dst = ft_strcpy(s2, dst);
	*dst = '\0';
	return (ptr);
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    char *original_dest = dest;

    while (n > 0 && *src)
	{
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    while (n > 0)
	{
        *dest = '\0';
        dest++;
        n--;
    }
    return (original_dest);
}
