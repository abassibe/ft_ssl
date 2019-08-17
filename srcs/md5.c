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

uint32_t convertAsLittleEndian(uint32_t n)
{
    char *tmp;
    int len;

    tmp = ft_itoa_base_maj_unsigned(((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) | (n << 24)), 16);
    len = ft_strlen(tmp);
    ft_strdel(&tmp);
    while (len < 8)
    {
        write(1, "0", 1);
        len++;
    }
    return ((n >> 24) | ((n & 0xff0000) >> 8) | ((n & 0xff00) << 8) | (n << 24));
}

static void cantWaitFor2020(t_ssl *ssl, uint32_t *f, int *g, size_t j)
{
    if (j < 16)
    {
        *f = (ssl->md5.b & ssl->md5.c) | (~ssl->md5.b & ssl->md5.d);
        *g = j;
    }
    else if (j < 32)
    {
        *f = (ssl->md5.d & ssl->md5.b) | (ssl->md5.c & ~ssl->md5.d);
        *g = (5 * j + 1) % 16;
    }
    else if (j < 48)
    {
        *f = (ssl->md5.b ^ ssl->md5.c ^ ssl->md5.d);
        *g = (3 * j + 5) % 16;
    }
    else
    {
        *f = (ssl->md5.c ^ (ssl->md5.b | ~ssl->md5.d));
        *g = (7 * j) % 16;
    }
}

static void hashWord(t_ssl *ssl, uint32_t *word)
{
    size_t j;
    int g;
    uint32_t f;

    j = 0;
    g = 0;
    f = 0;
    while (j < 64)
    {
        cantWaitFor2020(ssl, &f, &g, j);
        f = f + ssl->md5.a + ssl->md5.k[j] + word[g];
        ssl->md5.a = ssl->md5.d;
        ssl->md5.d = ssl->md5.c;
        ssl->md5.c = ssl->md5.b;
        ssl->md5.b = ssl->md5.b + ((f << ssl->md5.r[j]) | (f >> (32 - ssl->md5.r[j])));
        j += 1;
    }
}

static void processMd5(t_ssl *ssl)
{
    size_t i;
    unsigned char currBlock[65] = {0};
    uint32_t *word;

    i = 0;
    while (i < ssl->md5.newMessageLen)
    {
        ssl->md5.a = ssl->md5.buffA;
        ssl->md5.b = ssl->md5.buffB;
        ssl->md5.c = ssl->md5.buffC;
        ssl->md5.d = ssl->md5.buffD;
        ft_memcpy(currBlock, &ssl->md5.newMessage[i], 64);
        word = (uint32_t *)(ssl->md5.newMessage + i);
        hashWord(ssl, word);
        ssl->md5.buffA += ssl->md5.a;
        ssl->md5.buffB += ssl->md5.b;
        ssl->md5.buffC += ssl->md5.c;
        ssl->md5.buffD += ssl->md5.d;
        i += 64;
    }
    write(1, "MD5 = ", 6);
    ft_printf("%x", convertAsLittleEndian(ssl->md5.buffA));
    ft_printf("%x", convertAsLittleEndian(ssl->md5.buffB));
    ft_printf("%x", convertAsLittleEndian(ssl->md5.buffC));
    ft_printf("%x\n", convertAsLittleEndian(ssl->md5.buffD));
}

void md5FillString(t_ssl *ssl)
{
    unsigned long int lenBits;

    ssl->md5.blockCount = ((ssl->messageLen + 8) / 64) + 1;
    ssl->md5.newMessageLen = ssl->md5.blockCount * 64;
    if (!(ssl->md5.newMessage = ft_ustrnew(ssl->md5.newMessageLen)))
    {
        ft_putstr("Allocation error\n");
        exit(0);
    }
    ssl->md5.newMessage = ft_ustrcpy(ssl->md5.newMessage, ssl->message);
    ssl->md5.newMessage[ssl->messageLen] = 0x80;
    lenBits = 8 * ssl->messageLen;
    memcpy(ssl->md5.newMessage + (ssl->md5.newMessageLen - 8), &lenBits, 8);
    processMd5(ssl);
}
