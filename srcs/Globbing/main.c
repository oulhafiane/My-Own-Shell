/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:39:14 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/02 16:42:40 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int   main(int argc, char **argv)
{
  const char *stringstart;
  char *string = argv[1];
  for (stringstart = string;;)
  {
    string++;
    printf("%s\n", string);
  }
}
