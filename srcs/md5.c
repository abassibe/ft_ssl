/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:44:59 by abassibe          #+#    #+#             */
/*   Updated: 2019/08/15 17:45:03 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

unsigned int md5F0(unsigned int b, unsigned int c, unsigned int d)
{
    return (b & c) | (~b & d);
}

unsigned int md5F1(unsigned int b, unsigned int c, unsigned int d)
{
    return (d & b) | (~d & c);
}

unsigned int md5F2(unsigned int b, unsigned int c, unsigned int d)
{
    return (b ^ c ^ d);
}

unsigned int md5F3(unsigned int b, unsigned int c, unsigned int d)
{
    return (c ^ (b | ~d));
}

static void initializeBuffer(t_ssl *ssl)
{
    ssl->md5.buffA = 0x67452301;
    ssl->md5.buffB = 0xEFCDAB89;
    ssl->md5.buffC = 0x98BADCFE;
    ssl->md5.buffD = 0x10325476;
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

static void processMd5(t_ssl *ssl)
{
    size_t i;
    size_t j;
    int g;
    int tmp;
    unsigned a;
    unsigned b;
    unsigned c;
    unsigned d;
    unsigned f;
    unsigned char currBlock[65];
    currBlock[64] = 0;
    // unsigned word;
    unsigned int *w;

    i = 0;
    j = 0;

    unsigned int r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
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
    while (i < ssl->md5.newMessageLen)
    {
        a = ssl->md5.buffA;
        b = ssl->md5.buffB;
        c = ssl->md5.buffC;
        d = ssl->md5.buffD;
        memcpy(currBlock, &ssl->md5.newMessage[i], 64);
        w = subDividBlocks(currBlock);
        while (j < 16)
        {
            if (j < 4)
            {
                f = md5F0(b, c, d);
                g = i;
            }
            else if (j < 8)
            {
                f = md5F1(b, c, d);
                g = (5 * i + 1) % 16;
            }
            else if (j < 12)
            {
                f = md5F2(b, c, d);
                g = (3 * i + 5) % 16;
            }
            else
            {
                f = md5F3(b, c, d);
                g = (7 * i) % 16;
            }
            tmp = d;
            d = c;
            c = b;
            b = leftRotate((a + f + k[i] + w[g]), r[i]) + b;
            a = tmp;
            j += 1;
        }
        ssl->md5.buffA += a;
        ssl->md5.buffB += b;
        ssl->md5.buffC += c;
        ssl->md5.buffD += d;
        i += 64;
    }
    printf("MD5 = %x", ssl->md5.buffA);
    printf("%x", ssl->md5.buffB);
    printf("%x", ssl->md5.buffC);
    printf("%x\n", ssl->md5.buffD);
}

void md5FillString(t_ssl *ssl)
{
    unsigned int lenBits;

    ssl->md5.blockCount = ((ssl->messageLen + 8) / 64) + 1;
    ssl->md5.newMessageLen = ssl->md5.blockCount * 64;
    ssl->md5.newMessage = ft_ustrnew(ssl->md5.newMessageLen);
    ssl->md5.newMessage = ft_ustrcpy(ssl->md5.newMessage, ssl->message);
    ssl->md5.newMessage[ssl->messageLen] = 0x80;
    lenBits = 8 * ssl->messageLen;
    memcpy(ssl->md5.newMessage + (ssl->md5.newMessageLen - 8), &lenBits, 4);
    initializeBuffer(ssl);
    processMd5(ssl);
    // printf("[%hhu][%hhu][%hhu][%hhu][%hhu]\n", ssl->md5.newMessage[ssl->messageLen], ssl->md5.newMessage[ssl->md5.newMessageLen - 4], ssl->md5.newMessage[ssl->md5.newMessageLen - 3], ssl->md5.newMessage[ssl->md5.newMessageLen - 2], ssl->md5.newMessage[ssl->md5.newMessageLen - 1]);
    // printf("[%x][%x][%x][%x][%x]\n", ssl->md5.newMessage[ssl->messageLen], ssl->md5.newMessage[ssl->md5.newMessageLen - 4], ssl->md5.newMessage[ssl->md5.newMessageLen - 3], ssl->md5.newMessage[ssl->md5.newMessageLen - 2], ssl->md5.newMessage[ssl->md5.newMessageLen - 1]);
    // for (size_t i = 0; i < ssl->md5.newMessageLen; i++)
    //     printf("[%x]", ssl->md5.newMessage[i]);
    // printf("\n");
    // printf("ssl->messageLen = %u, [%x]\n", lenBits, lenBits);
}
