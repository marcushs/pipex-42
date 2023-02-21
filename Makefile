NAME			=	pipex
CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
LIB_FLAGS		=	-L libft -lft
DIR_SRCS		=	./srcs/
LIST_SRCS		=	pipex.c check_args.c parse.c free.c process.c
SRCS			=	${addprefix ${DIR_SRCS}, ${LIST_SRCS}}

DIR_OBJS		=	.objs/
LIST_OBJS		=	${LIST_SRCS:.c=.o}
OBJS			=	${addprefix ${DIR_OBJS}, ${LIST_OBJS}}

HEADERS			=	includes

LIB_FILES		=	${shell find libft -type f}
HEADER_FILES	=	${shell find includes -type f}

${DIR_OBJS}%.o:	${DIR_SRCS}%.c Makefile 
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

all:			${NAME}

${NAME}:		${DIR_OBJS} ${OBJS} ${LIB_FILES} ${HEADER_FILES}
				${MAKE} -C ./libft
				${CC} ${CFLAGS} ${OBJS} ${LIB_FLAGS} -o ${NAME}

${DIR_OBJS}:	
				mkdir -p ${DIR_OBJS} 

clean:
				${RM} ${DIR_OBJS}
				${MAKE} clean -C ./libft

fclean:			clean
				${MAKE} fclean -C ./libft
				${RM} ${NAME}

re:				fclean
				${MAKE} all

.PHONY:			all clean fclean re .c.o bonus
