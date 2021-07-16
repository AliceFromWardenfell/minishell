NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g # remove g-flag
HDRS	=	executor.h minishell.h
LIBS	= 	-lreadline
LIBFT	=	-L libft -lft

SRCS	=	executor.c \
			search_for_exec.c \
			global_error.c \
			builtins.c \
			echo.c \
			cd.c \
			pwd.c \
			env.c \
			export.c \
			env_funcs.c \
			add_funcs.c \
			\
			lexer.c \
			parser.c \
			signal.c \
			quote.c \
			env_parse.c \
			env_parse_utils_1.c \
			env_parse_utils_2.c \
			parser_lst_utils.c \
			pre-pipe.c \
			pipe_parse.c \
			pipe_parse_utils.c \
			pre_redirection.c \
			redirect_get.c \
			redirect_get_utils.c \
			redirect_parse.c \
			redirect_parse_utils_1.c \
			redirect_parse_utils_2.c \
			\
			minishell.c # tmp-main file, remove.
			

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

.c.o:		${HDRS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS} ${HDRS} ${LIBS}
			$(MAKE) -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} ${LIBFT} -o ${NAME} 

build:		all clean # remove.

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

lftclean: # remove?
			$(MAKE) clean -C libft

re:			fclean all

.PHONY:		all build clean lftclean fclean re
