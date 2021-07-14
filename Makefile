NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g#remove g-flag
HDRS	=	executor.h
LIBS	= 	-lreadline
LIBFT	=	-L libft -lft

SRCS	=	executor.c \
			global_error.c \
			builtins.c \
			echo.c \
			cd.c \
			pwd.c \
			env.c \
			export.c \
			env_funcs.c \
			add_funcs.c \
			main_for_executor.c #tmp file

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

.PHONY:		all build clean lftclean fclean re
