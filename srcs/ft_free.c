/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:12:27 by sdremora          #+#    #+#             */
/*   Updated: 2019/01/27 13:08:02 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>

/*
**	Освобождает память от всех ссылок из аргументов.
**	count_param указывает количество ссылок.
**	Всем значениям ссылок присваивается ноль.
*/

void	*ft_free(int count_param, ...)
{
	va_list ref_list;
	void	**reference;

	va_start(ref_list, count_param);
	while (count_param > 0)
	{
		reference = va_arg(ref_list, void **);
		free(*reference);
		*reference = NULL;
		count_param--;
	}
	va_end(ref_list);
	return (NULL);
}
