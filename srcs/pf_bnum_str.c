/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bnum_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:53:03 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:26:31 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_big_num.h"

static void	bnum_check_pow(t_bnum *bnum, char **str)
{
	int		len;
	int		pow;
	char	*temp;

	temp = *str;
	len = bnum->list_count;
	pow = bnum->power;
	if (pow == 0)
		ft_strncat(*str, ".0", 2);
	else if (len <= pow)
	{
		temp = ft_strnew(2 + pow);
		if (temp != NULL)
		{
			ft_strncat(temp, "0.", 2);
			while (pow-- > len)
				ft_strncat(temp, "0", 1);
			ft_strncat(temp, *str, len);
		}
		free(*str);
		*str = temp;
	}
	else
		ft_str_put(temp, len - pow, '.');
}

char		*pf_bnum_getstr(t_bnum *bnum)
{
	int		len;
	t_digit	*cur_digit;
	char	*str;
	char	temp;

	if (bnum == NULL)
		return (NULL);
	len = bnum->list_count * NUM_IN_DIGIT + 1 + 1;
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	cur_digit = bnum->digit_list;
	while (cur_digit != NULL)
	{
		temp = (cur_digit->value) + '0';
		ft_strncat(str, &temp, 1);
		cur_digit = cur_digit->previous;
	}
	bnum_check_pow(bnum, &str);
	return (str);
}
