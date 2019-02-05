/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:03:20 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:26:13 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Вставляет чар в строку, раздвигая её.
*/

int		ft_str_put(char *str, size_t index, char chr)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (index >= len)
		return (-1);
	i = len - 1;
	while (i >= index)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[index] = chr;
	return (0);
}
