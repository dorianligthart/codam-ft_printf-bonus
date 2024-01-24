/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:09:51 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/24 11:23:28 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdbool.h> // 'bool';

# ifdef DEBUG
#  include <stdio.h>
#  include <unistd.h>
#  include <limits.h>
#  include <string.h>
# endif

# ifndef ERROR_LIBFT
#  define ERROR_LIBFT -1
# endif

//printf()'s conversion data:
typedef struct s_conv
{
	bool	minus;
	bool	zero;
	bool	hash;
	bool	space;
	bool	plus;
	int		fw;
	bool	dot;
	int		precision;
	char	conv;
	int		len;
}	t_conv;

//printf()'s linked list:
typedef struct s_comp
{
	void			*item;
	t_conv			*conv;
	int				itemlen;
	struct s_comp	*next;
}	t_comp;

//linked list:
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//PDF ORDER:
//part 1 - ctype.h, string.h, strings.h, stdlib.h:
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size); //malloc()
char	*ft_strdup(const char *s); //malloc()

//part 2 - 42fr functions:
char	*ft_substr(char const *s, unsigned int start, size_t len); //malloc()
char	*ft_strjoin(char const *s1, char const *s2); //malloc()
char	*ft_strtrim(char const *s1, char const *set); //malloc()
char	**ft_split(char const *s, char c); //malloc(), free();
char	*ft_itoa(int n); //malloc(), ft_intlen();
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char)); //malloc()
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd); //write()
void	ft_putstr_fd(char *s, int fd); //write()
void	ft_putendl_fd(char *s, int fd); //write()
void	ft_putnbr_fd(int n, int fd); //write()

//bonus linked list:
t_list	*ft_lstnew(void *content); //malloc()
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *)); //free()
void	ft_lstclear(t_list **lst, void (*del)(void *)); //ft_lstdelone()
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
			// ft_lstclear(), ft_lstnew(), ft_lstadd_back();

//my own custom functions:
int		ft_intlen(int n, int base);
int		ft_longlen(long n, long base);

# ifndef LIBFT_VA_FORBIDDEN
void	ft_varray(char **array, const char *format, ...);
//		ft_printf:
int		ft_printf(const char *format, ...)
		__attribute__((format (printf, 1, 2))); //ft_printf_printcomp(),
			// ft_compclear(), ft_newcomp_append(), ft_newconv(),
			// ft_varray(), ft_strchr(), ft_atoi(),
			// ft_printf_getarglength(), ft_printf_getitemlength();
int		ft_printf_printcomp(int fd, t_comp *origin);
int		ft_printf_getitemlength(int conversion, void *item, t_conv *conv);
int		ft_printf_getarglength(int conversion, void *item);
//			ft_printf()'s struct functions:
void	ft_compclear(t_comp *comp);
t_comp	*ft_newcomp_append(t_comp **comp);
t_conv	*ft_newconv(void);
# endif

#endif
