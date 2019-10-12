/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:25:11 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/08 14:21:46 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		num_len(int nbr)
{
	int len;

	len = (nbr > 0) ? 0 : 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	len = num_len(n);
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if ((string = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	string[len--] = '\0';
	while (len >= 0)
	{
		string[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	if (sign)
		string[0] = '-';
	return (string);
}
