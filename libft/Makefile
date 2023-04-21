# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 13:20:40 by hleung            #+#    #+#              #
#    Updated: 2023/04/21 11:47:06 by hleung           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc ${CFLAGS}

RM		=	rm -f

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_split.c ft_strchr.c ft_strchr_int.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c ft_putadd.c ft_putchar.c ft_putnbr.c  ft_putnbr_base.c ft_putstr.c ft_putnbr_unsigned.c get_next_line.c ft_strcmp.c

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c

BOBJS	=	${BONUS:.c=.o}

OBJS	=	${SRCS:.c=.o}

HEADER	=	.

%.o:		%.c $(HEADER) Makefile
			${CC} -c $< -o ${<:.c=.o} -I ${HEADER}

all:		${NAME}
${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}
bonus:		${NAME} ${BOBJS}
			ar rcs ${NAME} ${BOBJS}

clean:
			${RM} ${OBJS} ${BOBJS}
fclean:		clean
			${RM} ${NAME}
re:			fclean all
.PHONY: all clean fclean re .c.o

