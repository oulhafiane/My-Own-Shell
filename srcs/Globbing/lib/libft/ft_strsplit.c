/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 18:25:07 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/06 17:20:48 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_words(char *s, char c)
{
	int counter;

	counter = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			counter++;
		while (*s && *s != c)
			s++;
	}
	return (counter);
}

int		word_len(char *str, char c)
{
	int counter;

	counter = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		while (*str != c && *str)
		{
			counter++;
			str++;
		}
		break ;
	}
	return (counter);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**words;
	int		len;
	int		j;
	int		index;

	index = 0;
	len = ft_words((char *)s, c);
	if ((words = (char **)malloc(sizeof(char *) * len + 1)) == NULL)
		return (NULL);
	while (*s && len-- > 0)
	{
		while (*s == c && *s)
			s++;
		words[index] = ft_strnew((size_t)word_len((char *)s, c));
		j = 0;
		while (*s && *s != c)
			words[index][j++] = *s++;
		words[index][j] = '\0';
		index++;
	}
	words[index] = 0;
	return (words);
}
