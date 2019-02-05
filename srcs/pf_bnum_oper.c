/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bnum_oper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:06:24 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/05 09:26:21 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_big_num.h"

static void	bnum_equal_power(t_bnum *num1, t_bnum *num2)
{
	t_bnum	*a;
	t_bnum	*b;
	t_digit	*temp;

	a = (num1->power <= num2->power) ? num1 : num2;
	b = (num1->power <= num2->power) ? num2 : num1;
	temp = a->digit_list;
	while (temp->previous != NULL)
		temp = temp->previous;
	while (a->power < b->power)
	{
		temp = pf_bnum_get_previous(a, temp);
		if (temp == NULL)
			return ;
		(a->power)++;
	}
}

void		pf_bnum_plus_bnum(t_bnum *num1, t_bnum *num2)
{
	t_digit	*digit_a;
	t_digit	*digit_b;

	bnum_equal_power(num1, num2);
	digit_a = num1->digit_list;
	digit_b = num2->digit_list;
	while (digit_a->previous != NULL)
		digit_a = digit_a->previous;
	while (digit_b->previous != NULL)
		digit_b = digit_b->previous;
	while (digit_b != NULL)
	{
		pf_bnum_digit_plus(num1, digit_a, digit_b->value);
		digit_b = digit_b->next;
		if (digit_b != NULL)
			digit_a = pf_bnum_get_next_digit(num1, digit_a);
	}
}

void		pf_bnum_digit_plus(t_bnum *bnum, t_digit *digit, int value)
{
	digit->value += value;
	if (digit->value >= MAX_VALUE)
	{
		value = digit->value / MAX_VALUE;
		digit->value %= MAX_VALUE;
		digit = pf_bnum_get_next_digit(bnum, digit);
		if (digit == NULL)
			return ;
		pf_bnum_digit_plus(bnum, digit, value);
	}
}

void		pf_bnum_2multdiv(t_bnum *bnum, char operate)
{
	t_digit *cur_digit;
	t_digit *next_digit;
	int		value;

	cur_digit = bnum->digit_list;
	while (cur_digit != NULL)
	{
		cur_digit->value *= (operate == '*') ? 2 : 5;
		if (cur_digit->value >= MAX_VALUE)
		{
			value = cur_digit->value / MAX_VALUE;
			cur_digit->value = cur_digit->value % MAX_VALUE;
			next_digit = pf_bnum_get_next_digit(bnum, cur_digit);
			if (next_digit == NULL)
				return ;
			pf_bnum_digit_plus(bnum, next_digit, value);
		}
		cur_digit = cur_digit->previous;
	}
	if (operate == '/')
		(bnum->power)++;
}

void		pf_bnum_free(t_bnum *num)
{
	t_digit	*cur_digit;
	t_digit	*prev_digit;

	if (num != NULL)
	{
		cur_digit = num->digit_list;
		while (cur_digit != NULL)
		{
			prev_digit = cur_digit->previous;
			free(cur_digit);
			cur_digit = prev_digit;
		}
	}
	free(num);
}
