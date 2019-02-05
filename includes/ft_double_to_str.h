/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_to_str.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdremora <sdremora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:34:58 by sdremora          #+#    #+#             */
/*   Updated: 2019/02/03 16:31:29 by sdremora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOUBLE_TO_STR_H
# define FT_DOUBLE_TO_STR_H
# define DBL_EXP_LEN 11
# define DBL_EXP_OFFSET 1023
# define LDBL_EXP_LEN 15

/*
**	у long double первый бит всегда явная единица оО
*/

# define LDBL_EXP_OFFSET 16383

# include "ft_printf.h"
# include "ft_big_num.h"

char			*pf_double_to_str(char	*sp, ...);
int				pf_get_exponent(char *bits, int start, int len);
struct s_bnum	*pf_get_mantissa(char *bits, int start, int expon);
char			*pf_check_boards(char *bits, char type);

#endif
