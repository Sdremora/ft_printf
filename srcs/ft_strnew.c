/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:43:40 by sdremora          #+#    #+#             */
/*   Updated: 2018/12/07 11:21:03 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*link;
	size_t	i;
	size_t	limit;

	limit = -1;
	if (size == limit)
		return (NULL);
	link = (char *)malloc(sizeof(*link) * (size + 1));
	if (link == NULL)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		link[i] = '\0';
		i++;
	}
	return (link);
}
