CC		=	gcc
NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror
HDRS	=	executor.h
RM		=	rm -f
SRCS	=	executor.c
OBJS	=	${SRCS:.c=.o}
LIBS	= 	-lreadline

.c.o:		${HDRS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS} ${HDRS} ${LIBS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

build:		all clean

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all build clean fclean re
