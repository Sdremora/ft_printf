/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_big_num.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:36:19 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/03 17:33:10 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIG_NUM_H

# define FT_BIG_NUM_H
# define NUM_IN_DIGIT 1
# define MAX_VALUE 10

# include "ft_printf.h"

/*
**	1875	pow = -4 -> 0,1875
**	3750	pow = -4 -> 0,3750
**	7500	pow = -4 -> 0,7500
**	15000	pow = -4 -> 1,5000
**
**	1		pow = 0 -> 1,0
**	5		pow = -1 -> 0,5
**	25		pow = -2 -> 0,25
**	125		pow = -3 -> 0,125
*/

typedef	struct		s_digit
{
	unsigned char	value;
	struct s_digit	*next;
	struct s_digit	*previous;
}					t_digit;

typedef	struct		s_bnum
{
	t_digit	*digit_list;
	int		list_count;
	int		power;
}					t_bnum;

char				*pf_bnum_getstr(t_bnum *bnum);
t_digit				*pf_bnum_digit_ini();
t_bnum				*pf_bnum_ini(unsigned char sign);
t_digit				*pf_bnum_get_next_digit(t_bnum *bnum, t_digit	*digit);
void				pf_bnum_digit_plus(t_bnum *bnum, t_digit *digit, int value);
t_digit				*pf_bnum_get_previous(t_bnum *num, t_digit *digit);
void				pf_bnum_free(t_bnum *num);
void				pf_bnum_plus_bnum(t_bnum *num1, t_bnum *num2);
void				pf_bnum_2multdiv(t_bnum *bnum, char operate);

#endif
