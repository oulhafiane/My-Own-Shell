/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 08:32:32 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/11 09:18:19 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char		*ft_strndup(const char *s1, size_t n)
{
	char	*string;
	size_t	len;

	if (s1 && (len = strlen(s1)))
		if ((string = (char *)malloc(sizeof(char) * len + 1)) == NULL)
			return (NULL);
	strncat(string, s1, n);
	return (string);
}

int		main(int argc, char **argv)
{
	if (argc > 2)
		printf("%s\n", ft_strndup(argv[1], atoi(argv[2])));
	return (0);
}
