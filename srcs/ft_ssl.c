/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:14:31 by abassibe          #+#    #+#             */
/*   Updated: 2019/08/15 17:14:33 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned char *ft_ustrnew(size_t size)
{
	unsigned char *m;
	size_t c;

	c = 0;
	if (!(m = (unsigned char *)malloc(size + 1)))
		return (NULL);
	while (c != size)
	{
		m[c] = 0;
		c++;
	}
	m[c] = 0;
	return (m);
}

unsigned char *ft_ustrcpy(unsigned char *dst, unsigned char *src)
{
	size_t k;

	k = 0;
	while (src[k])
	{
		dst[k] = (unsigned char)src[k];
		k++;
	}
	dst[k] = 0;
	return (dst);
}

int readAndInitialize(t_ssl *ssl, char **av)
{
	char *str;
	char *buffer;
	int fd;
	int len;

	if ((fd = open(av[1], O_RDONLY)) < 3)
	{
		ft_printf("Cannot open file.\n");
		return (0);
	}
	str = ft_strnew(1);
	buffer = ft_strnew(50);
	while ((len = read(fd, buffer, 50)) > 0)
	{
		str = ft_strjoinff(str, buffer);
		buffer = ft_memset(buffer, 0, 50);
	}
	ssl->message = (unsigned char *)str;
	ssl->messageLen = ft_strlen(str);
	free(str);
	if (len < 0)
	{
		ft_printf("Error while reading.\n");
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_ssl ssl;

	if (ac > 1 && !readAndInitialize(&ssl, av))
		return (-1);
	else if (ac == 1)
		return (0); //TODO: lecture depuis STDIN
	md5FillString(&ssl);
	return (0);
}
