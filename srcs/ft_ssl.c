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

unsigned int f0(unsigned int b, unsigned int c, unsigned int d)
{
	return (b & c) | (~b & d);
}

unsigned int f1(unsigned int b, unsigned int c, unsigned int d)
{
	return (d & b) | (~d & c);
}

unsigned int f2(unsigned int b, unsigned int c, unsigned int d)
{
	return (b ^ c ^ d);
}

unsigned int f3(unsigned int b, unsigned int c, unsigned int d)
{
	return (c ^ (b | ~d));
}

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

void fillString(t_ssl ssl)
{
	unsigned char *buffer;
	unsigned char *newMessage;
	size_t bufferCount;
	size_t newMesageLen;
	unsigned int lenBits;

	bufferCount = ((ssl.messageLen + 8) / 64) + 1;
	newMesageLen = bufferCount * 64;
	newMessage = ft_ustrnew(newMesageLen);
	newMessage = ft_ustrcpy(newMessage, ssl.message);
	newMessage[ssl.messageLen] = 0x80;
	lenBits = 8 * ssl.messageLen;
	memcpy(newMessage + (newMesageLen - 8), &lenBits, 4);
	// printf("[%hhu][%hhu][%hhu][%hhu][%hhu]\n", newMessage[ssl.messageLen], newMessage[newMesageLen - 4], newMessage[newMesageLen - 3], newMessage[newMesageLen - 2], newMessage[newMesageLen - 1]);
	// printf("[%x][%x][%x][%x][%x]\n", newMessage[ssl.messageLen], newMessage[newMesageLen - 4], newMessage[newMesageLen - 3], newMessage[newMesageLen - 2], newMessage[newMesageLen - 1]);
	// printf("ssl.messageLen = %lu, [%zx]\n", ssl.messageLen, ssl.messageLen);
	// for (int i = 0; i < newMesageLen; i++)
	// 	printf("[%x]", newMessage[i]);
	// printf("\n");
}

int main(int ac, char **av)
{
	char *str;
	char *buffer;
	int fd;
	int len;
	t_ssl ssl;

	if ((fd = open(av[1], O_RDONLY)) < 3)
	{
		ft_printf("Cannot open file.\n");
		return (1);
	}
	str = ft_strnew(1);
	buffer = ft_strnew(50);
	while ((len = read(fd, buffer, 50)) > 0)
	{
		str = ft_strjoinff(str, buffer);
		buffer = ft_memset(buffer, 0, 50);
	}
	ssl.message = (unsigned char *)str;
	ssl.messageLen = ft_strlen(str);
	free(str);

	if (len < 0)
	{
		ft_printf("Error while reading.\n");
		return (1);
	}
	fillString(ssl);
	return (0);
}
