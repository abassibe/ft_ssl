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

void fillStrcutPattern(t_ssl *ssl)
{
	unsigned int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
						  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
						  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
						  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	unsigned int k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
						  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
						  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
						  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
						  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
						  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
						  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
						  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	ssl->md5.k = (unsigned int *)malloc(64 * sizeof(unsigned int));
	ssl->md5.r = (unsigned int *)malloc(64 * sizeof(unsigned int));
	for (int i = 0; i < 64; i++)
	{
		ssl->md5.k[i] = k[i];
		ssl->md5.r[i] = r[i];
	}
	ssl->md5.buffA = 0x67452301;
	ssl->md5.buffB = 0xEFCDAB89;
	ssl->md5.buffC = 0x98BADCFE;
	ssl->md5.buffD = 0x10325476;
}

int main(int ac, char **av)
{
	t_ssl *ssl;

	ssl = (t_ssl *)malloc(sizeof(t_ssl));

	if (ac > 1 && !readAndInitialize(ssl, av))
		return (-1);
	else if (ac == 1)
		return (0); //TODO: lecture depuis STDIN
	fillStrcutPattern(ssl);
	md5FillString(ssl);
	return (0);
}
