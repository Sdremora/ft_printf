/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:27:01 by sdremora          #+#    #+#             */
/*   Updated: 2019/01/30 16:47:37 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_get_bits(void *data, int data_bytes_count)
{
	int		i;
	int		n;
	int		mask;
	char	*bytes;
	char	*mem;

	bytes = ft_strnew(data_bytes_count * 8);
	mem = ft_strnew(data_bytes_count);
	if (!bytes || !mem)
		return (ft_free(2, &bytes, &mem));
	ft_memcpy(mem, data, data_bytes_count);
	i = 0;
	while (i < data_bytes_count)
	{
		mask = 1;
		n = 0;
		while (n < 8)
		{
			bytes[n + i * 8] = (mem[i] & (mask << n)) > 0 ? '1' : '0';
			n++;
		}
		i++;
	}
	free(mem);
	return (bytes);
}
