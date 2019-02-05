/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bnum_sup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:06:24 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/03 15:22:28 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_big_num.h"

t_digit		*pf_bnum_digit_ini(void)
{
	t_digit	*digit;

	digit = (t_digit *)malloc(sizeof(t_digit));
	if (digit == NULL)
		return (NULL);
	digit->value = 0;
	digit->next = NULL;
	digit->previous = NULL;
	return (digit);
}

t_bnum		*pf_bnum_ini(unsigned char ini)
{
	t_bnum	*bnum;
	t_digit	*digit;

	bnum = (t_bnum *)malloc(sizeof(t_bnum));
	if (bnum == NULL)
		return (NULL);
	bnum->power = 0;
	digit = pf_bnum_digit_ini();
	if (digit == NULL)
	{
		free(bnum);
		return (NULL);
	}
	digit->value = (ini > 9) ? 9 : ini;
	bnum->digit_list = digit;
	bnum->list_count = 1;
	return (bnum);
}

t_digit		*pf_bnum_get_next_digit(t_bnum *bnum, t_digit *digit)
{
	t_digit	*cur_digit;
	t_digit	*next_digit;

	cur_digit = bnum->digit_list;
	while (cur_digit != digit)
		cur_digit = cur_digit->previous;
	if (cur_digit->next == NULL)
	{
		next_digit = pf_bnum_digit_ini();
		if (next_digit == NULL)
			return (NULL);
		next_digit->previous = cur_digit;
		cur_digit->next = next_digit;
		(bnum->list_count)++;
		bnum->digit_list = next_digit;
	}
	else
		next_digit = cur_digit->next;
	return (next_digit);
}

t_digit		*pf_bnum_get_previous(t_bnum *num, t_digit *digit)
{
	t_digit	*cur_dig;
	t_digit	*temp;

	cur_dig = num->digit_list;
	while (cur_dig != digit)
		cur_dig = cur_dig->previous;
	if (cur_dig->previous == NULL)
	{
		temp = pf_bnum_digit_ini();
		if (temp == NULL)
			return (NULL);
		temp->next = cur_dig;
		cur_dig->previous = temp;
		(num->list_count)++;
	}
	return (cur_dig->previous);
}
