# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hleung <hleung@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 14:27:32 by hleung            #+#    #+#              #
#    Updated: 2023/05/15 12:48:13 by hleung           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

NAME			=	pipex
BONUS			=	pipex_b
CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	./libft/libft.a
LIB_FLAGS		=	-L libft -lft
DIR_M_SRCS		=	./srcs/mandatory/
LIST_M_SRCS		=	pipex.c check_bin.c parse.c free.c process.c wait.c 
M_SRCS			=	${addprefix ${DIR_M_SRCS}, ${LIST_M_SRCS}}

DIR_B_SRCS		=	./srcs/bonus/
LIST_B_SRCS		=	pipex_b.c parse_b.c check_bin_b.c free_b.c linked_list.c process_b.c here_doc.c
B_SRCS			=	${addprefix ${DIR_B_SRCS}, ${LIST_B_SRCS}}

DIR_M_OBJS		=	.objs/
LIST_M_OBJS		=	${LIST_M_SRCS:.c=.o}
M_OBJS			=	${addprefix ${DIR_M_OBJS}, ${LIST_M_OBJS}}

DIR_B_OBJS		=	.objs_b/
LIST_B_OBJS		=	${LIST_B_SRCS:.c=.o}
B_OBJS			=	${addprefix ${DIR_B_OBJS}, ${LIST_B_OBJS}}

HEADERS			=	includes

${DIR_M_OBJS}%.o:	${DIR_M_SRCS}%.c Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

${DIR_B_OBJS}%.o:	${DIR_B_SRCS}%.c Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

all:			${NAME}

bonus:			${BONUS}

${NAME}:		${DIR_M_OBJS} ${M_OBJS} ${LIB} ./includes/pipex.h
				${CC} ${CFLAGS} -g ${M_OBJS} ${LIB_FLAGS} -o ${NAME}
				@echo "${GREEN}Compiled pipex! ${NC}"

${BONUS}:		${DIR_B_OBJS} ${B_OBJS} ${LIB} ./includes/pipex_b.h
				${CC} ${CFLAGS} -g ${B_OBJS} -o ${BONUS} ${LIB_FLAGS}
				@echo "${GREEN}Compiled pipex_b! ${NC}"

${DIR_M_OBJS}:	
				mkdir -p ${DIR_M_OBJS}

${DIR_B_OBJS}:	
				mkdir -p ${DIR_B_OBJS}

${LIB}:			force
				${MAKE} -sC ./libft

clean:
				${RM} ${DIR_M_OBJS} ${DIR_B_OBJS}
				${MAKE} clean -sC ./libft
				@echo "${YELLOW}Object files and libraries cleared!${NC}"

fclean:			clean
				${MAKE} fclean -sC ./libft
				${RM} ${NAME} ${BONUS}
				@echo "${YELLOW}Executable cleared!${NC}"

re:				fclean
				${MAKE} all

.SILENT:

.PHONY:			all clean fclean re .c.o bonus force
