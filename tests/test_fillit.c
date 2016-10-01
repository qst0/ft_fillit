/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fillit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 20:57:31 by myoung            #+#    #+#             */
/*   Updated: 2016/10/01 08:18:36 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <unistd.h>

#define OXXX write(fd, "o...\n", 5);
#define XOXX write(fd, ".o..\n", 5);
#define XXOX write(fd, "..o.\n", 5);
#define XXXO write(fd, "...o\n", 5);
#define XXXX write(fd, "....\n", 5);
#define OOXX write(fd, "oo..\n", 5);
#define OOOX write(fd, "ooo.\n", 5);
#define OOOO write(fd, "oooo\n", 5);
#define XOOO write(fd, ".ooo\n", 5);
#define XXOX write(fd, "..oo\n", 5);

/*
 * Read in a string of up to 26 chars
 * count how many chars
 */

void	line_v(int fd)
{
	OXXX
	OXXX
	OXXX
	OXXX
}

int		main(int argc , char **argv)
{
	argc = 0;
	argv = 0;
	line_v(1);;
}
