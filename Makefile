NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HDRS	=	executor.h
LIBS	= 	-lreadline
LIBFT	=	-L libft -lft

SRCS	=	executor.c
OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

.c.o:		${HDRS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS} ${HDRS} ${LIBS}
			$(MAKE) -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} ${LIBFT} -o ${NAME} 

build:		all clean

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

lftclean:
			$(MAKE) clean -C libft

re:			fclean all

.PHONY:		all build clean fclean re
