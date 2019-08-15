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

void md5FillString(t_ssl ssl)
{
    unsigned int lenBits;

    ssl.md5.blockCount = ((ssl.messageLen + 8) / 64) + 1;
    ssl.md5.newMesageLen = ssl.md5.blockCount * 64;
    ssl.md5.newMessage = ft_ustrnew(ssl.md5.newMesageLen);
    ssl.md5.newMessage = ft_ustrcpy(ssl.md5.newMessage, ssl.message);
    ssl.md5.newMessage[ssl.messageLen] = 0x80;
    lenBits = 8 * ssl.messageLen;
    memcpy(ssl.md5.newMessage + (ssl.md5.newMesageLen - 8), &lenBits, 4);
    // printf("[%hhu][%hhu][%hhu][%hhu][%hhu]\n", ssl.md5.newMessage[ssl.messageLen], ssl.md5.newMessage[ssl.md5.newMesageLen - 4], ssl.md5.newMessage[ssl.md5.newMesageLen - 3], ssl.md5.newMessage[ssl.md5.newMesageLen - 2], ssl.md5.newMessage[ssl.md5.newMesageLen - 1]);
    // printf("[%x][%x][%x][%x][%x]\n", ssl.md5.newMessage[ssl.messageLen], ssl.md5.newMessage[ssl.md5.newMesageLen - 4], ssl.md5.newMessage[ssl.md5.newMesageLen - 3], ssl.md5.newMessage[ssl.md5.newMesageLen - 2], ssl.md5.newMessage[ssl.md5.newMesageLen - 1]);
    // printf("ssl.messageLen = %lu, [%zx]\n", ssl.messageLen, ssl.messageLen);
    // for (size_t i = 0; i < ssl.md5.newMesageLen; i++)
    //     printf("[%x]", ssl.md5.newMessage[i]);
    // printf("\n");
}
