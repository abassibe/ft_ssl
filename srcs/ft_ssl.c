#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "../includes/libft.h"

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

unsigned char *ft_ustrcpy(unsigned char *dst, const char *src)
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

unsigned char *completMessage(char *message, int messageLen)
{
	unsigned char *buffer;
	size_t bufferLen;

	bufferLen = ((((messageLen * 8) + 64) / 512) + 1) * 64;
	buffer = ft_ustrnew(bufferLen);
	buffer = ft_ustrcpy(buffer, message);
	buffer[messageLen] |= 0x01;
	buffer[bufferLen - 1] = (unsigned char)(bufferLen >> 0u) & 0xFF;
	buffer[bufferLen - 2] = (unsigned char)(bufferLen >> 8u) & 0xFF;
	buffer[bufferLen - 3] = (unsigned char)(bufferLen >> 16u) & 0xFF;
	buffer[bufferLen - 4] = (unsigned char)(bufferLen >> 32u) & 0xFF;
	return (buffer);
}

unsigned int *subDividBlocks(unsigned char *block)
{
	int i;
	int j;
	unsigned int *subDivided = (unsigned int *)malloc(16 * sizeof(unsigned int));

	i = 0;
	j = 0;
	while (j < 16)
	{
		subDivided[j] = (block[i] << 24) | (block[i + 1] << 16) | (block[i + 2] << 8) | block[i + 3];
		i += 4;
		j++;
	}
	return (subDivided);
}

unsigned int leftRotate(unsigned int v, short int amt)
{
	unsigned int msk1;

	msk1 = (1 << amt) - 1;
	return ((v >> (32 - amt)) & msk1) | ((v << amt) & ~msk1);
}

void processing(unsigned char *buffer, size_t bufferLen)
{
	unsigned int h0 = 0x67452301;
	unsigned int h1 = 0xEFCDAB89;
	unsigned int h2 = 0x98BADCFE;
	unsigned int h3 = 0x10325476;
	unsigned int k[64];
	unsigned int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
						  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
						  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
						  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	int block;
	int i = 0;

	while (i < 64)
	{
		k[i] = (unsigned int)floor(fabs(sin(i + 1)) * pow(2, 32));
		i++;
	}

	block = 0;
	while (block < bufferLen / 64)
	{
		unsigned int a = h0;
		unsigned int b = h1;
		unsigned int c = h2;
		unsigned int d = h3;
		unsigned int f = 0;
		unsigned int g = 0;
		unsigned int *w;

		w = subDividBlocks(&buffer[block]);
		i = 0;
		while (i < 64)
		{
			if (i < 16)
			{
				f = f0(h1, h2, h3);
				g = i;
			}
			else if (i < 32)
			{
				f = f1(h1, h2, h3);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = f2(h1, h2, h3);
				g = (3 * i + 5) % 16;
			}
			else
			{
				f = f3(h1, h2, h3);
				g = (7 * i) % 16;
			}
			unsigned int tmp = d;
			d = c;
			c = b;
			b = leftRotate(a + f + k[i] + w[g], r[i]);
			a = tmp;
			i++;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		block += 64;
		free(w);
	}
	printf("%x%x%x%x\n", h0, h1, h2, h3);
}

int main(int ac, char **av)
{
	size_t inputLen;
	char *buffer;
	unsigned char *buffer2;
	char *message;

	message = ft_strnew(1);
	// while (ac == 1 && get_next_line(0, &buffer))
	// {
	// 	message = ft_strjoin(message, buffer);
	// }
	int fd = open("tst", O_RDONLY);
	while (ac == 1 && get_next_line(fd, &buffer))
	{
		message = ft_strjoin(message, buffer);
	}
	if (ac == 2)
		message = av[1];
	inputLen = ft_strlen(message);
	buffer2 = completMessage(message, inputLen);
	processing(buffer2, inputLen);
}
