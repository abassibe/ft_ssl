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

unsigned int *subDividBlocks(unsigned char *block)
{
    int i;
    int j;
    unsigned int *subDivided;

    i = 0;
    j = 0;
    subDivided = (unsigned int *)malloc(16 * sizeof(unsigned int));
    subDivided = ft_memset(subDivided, 0, 16 * sizeof(unsigned int));
    while (j < 16)
    {
        subDivided[j] = (block[i] << 24) | (block[i + 1] << 16) | (block[i + 2] << 8) | block[i + 3];
        i += 4;
        j++;
    }
    return (subDivided);
}

unsigned int leftRotate(unsigned int x, short int c)
{
    return (x << c) | (x >> (32 - c));
}

static void processMd5(t_ssl *ssl)
{
    size_t i;
    size_t j;
    int g;
    unsigned a;
    unsigned b;
    unsigned c;
    unsigned d;
    unsigned f;
    unsigned char currBlock[65] = {0};
    currBlock[64] = 0;
    unsigned int *word;

    i = 0;
    j = 0;
    g = 0;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    f = 0;

    while (i < 8 * ssl->md5.newMessageLen)
    {
        a = ssl->md5.buffA;
        b = ssl->md5.buffB;
        c = ssl->md5.buffC;
        d = ssl->md5.buffD;
        memcpy(currBlock, &ssl->md5.newMessage[i / 8], 64);
        word = subDividBlocks(currBlock);
        while (j < 64)
        {
            if (j < 16)
            {
                f = md5F0(b, c, d);
                g = j;
            }
            else if (j < 32)
            {
                f = md5F1(b, c, d);
                g = (5 * j + 1) % 16;
            }
            else if (j < 48)
            {
                f = md5F2(b, c, d);
                g = (3 * j + 5) % 16;
            }
            else
            {
                f = md5F3(b, c, d);
                g = (7 * j) % 16;
            }
            f = f + a + ssl->md5.k[j] + word[g];
            a = d;
            d = c;
            c = b;
            b = b + leftRotate(f, ssl->md5.r[j]);
            j += 1;
        }
        free(word);
        j = 0;
        ssl->md5.buffA += a;
        ssl->md5.buffB += b;
        ssl->md5.buffC += c;
        ssl->md5.buffD += d;
        i += 512;
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
    processMd5(ssl);
    // printf("[%hhu][%hhu][%hhu][%hhu][%hhu]\n", ssl->md5.newMessage[ssl->messageLen], ssl->md5.newMessage[ssl->md5.newMessageLen - 4], ssl->md5.newMessage[ssl->md5.newMessageLen - 3], ssl->md5.newMessage[ssl->md5.newMessageLen - 2], ssl->md5.newMessage[ssl->md5.newMessageLen - 1]);
    // printf("[%x][%x][%x][%x][%x]\n", ssl->md5.newMessage[ssl->messageLen], ssl->md5.newMessage[ssl->md5.newMessageLen - 4], ssl->md5.newMessage[ssl->md5.newMessageLen - 3], ssl->md5.newMessage[ssl->md5.newMessageLen - 2], ssl->md5.newMessage[ssl->md5.newMessageLen - 1]);
    // for (size_t i = 0; i < ssl->md5.newMessageLen; i++)
    //     printf("[%x]", ssl->md5.newMessage[i]);
    // printf("\n");
    // printf("ssl->messageLen = %u, [%x]\n", lenBits, lenBits);
}
