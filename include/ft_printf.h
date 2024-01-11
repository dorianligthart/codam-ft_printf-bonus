/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/11 20:09:00 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef ERROR_FT_PRINTF
#  define ERROR_FT_PRINTF -1
# endif

int	ft_printf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));

#endif // FT_PRINTF_H