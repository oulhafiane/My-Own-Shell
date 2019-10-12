/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 11:08:18 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/09 09:57:09 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, const char *src, int nb)
{
	char *ret;

	ret = dest;
	while (*dest)
		dest++;
	while (nb--)
		if (!(*dest++ = *src++))
			return (ret);
	*dest = 0;
	return (ret);
}
