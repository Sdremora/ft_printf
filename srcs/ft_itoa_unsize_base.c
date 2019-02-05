/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsize_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:35:27 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:25:47 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEX_SMALL "0123456789abcdef"

char		*ft_itoa_unsize_base(size_t dec_num, int base)
{
	char	*result;
	size_t	temp;
	int		count;

	count = 1;
	temp = dec_num;
	while ((temp = temp / base) != 0)
		count++;
	result = ft_strnew(count);
	if (result == NULL)
		return (NULL);
	while (count > 0)
	{
		count--;
		temp = dec_num % base;
		dec_num /= base;
		result[count] = HEX_SMALL[temp];
	}
	return (result);
}
