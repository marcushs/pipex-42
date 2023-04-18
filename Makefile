NAME			=	pipex
BONUS			=	pipex_b
CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror #-fsanitize=address
LIB_FLAGS		=	-L libft -lft
DIR_M_SRCS		=	./srcs/mandatory/
LIST_M_SRCS		=	pipex.c check_bin.c parse.c free.c process.c wait.c 
M_SRCS			=	${addprefix ${DIR_M_SRCS}, ${LIST_M_SRCS}}

DIR_B_SRCS		=	./srcs/bonus/
LIST_B_SRCS		=	pipex_b.c parse_b.c check_bin_b.c free_b.c linked_list.c process_b.c wait_b.c
B_SRCS			=	${addprefix ${DIR_B_SRCS}, ${LIST_B_SRCS}}

DIR_M_OBJS		=	.objs/
LIST_M_OBJS		=	${LIST_M_SRCS:.c=.o}
M_OBJS			=	${addprefix ${DIR_M_OBJS}, ${LIST_M_OBJS}}

DIR_B_OBJS		=	.objs_b/
LIST_B_OBJS		=	${LIST_B_SRCS:.c=.o}
B_OBJS			=	${addprefix ${DIR_B_OBJS}, ${LIST_B_OBJS}}

HEADERS			=	includes

LIB_FILES		=	${shell find libft -type f}
HEADER_FILES	=	${shell find includes -type f}

${DIR_M_OBJS}%.o:	${DIR_M_SRCS}%.c Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

${DIR_B_OBJS}%.o:	${DIR_B_SRCS}%.c Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

all:			${NAME}

bonus:			${BONUS}

${NAME}:		${DIR_M_OBJS} ${M_OBJS} ${LIB_FILES} ${HEADER_FILES}
				${MAKE} bonus -C ./libft
				${CC} ${CFLAGS} ${M_OBJS} ${LIB_FLAGS} -o ${NAME}

${BONUS}:		${DIR_B_OBJS} ${B_OBJS} ${LIB_FILES} ${HEADER_FILES}
				${MAKE} bonus -C ./libft
				${CC} ${CFLAGS} ${B_OBJS} ${LIB_FLAGS} -o ${BONUS}

${DIR_M_OBJS}:	
				mkdir -p ${DIR_M_OBJS} 

${DIR_B_OBJS}:	
				mkdir -p ${DIR_B_OBJS} 

clean:
				${RM} ${DIR_M_OBJS} ${DIR_B_OBJS}
				${MAKE} clean -C ./libft

fclean:			clean
				${MAKE} fclean -C ./libft
				${RM} ${NAME} ${BONUS}

re:				fclean
				${MAKE} all

.PHONY:			all clean fclean re .c.o bonus
