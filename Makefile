#VAR
NAME			=	pipex
CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

#HEADER
HEADER_SRCS		=	pipex.h
HEADER_DIR		=	includes/
HEADER			=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

#MANDATORY
MAND_SRCS		=	pipex.c error.c free.c path.c childs.c
MAND_PATH_DIR	=	mandatory/
MAND_PATH		=	$(addprefix $(MAND_PATH_DIR), $(MAND_SRCS))
MAND_OBJ		=	$(MAND_PATH:.c=.o)

#LIBFT
LIBFT_SRCS		=	ft_bzero.c ft_calloc.c ft_split.c \
					ft_strjoin.c ft_strlen.c ft_strncmp.c \
					ft_strchr.c
LIBFT_PATH_DIR	=	libft/
LIBFT_PATH		=	$(addprefix $(LIBFT_PATH_DIR), $(LIBFT_SRCS))
LIBFT_OBJ		=	$(LIBFT_PATH:.c=.o)

#COMMAND
%.o: %.c $(HEADER) Makefile
					@${CC} ${FLAGS} -c $< -o $@

$(NAME):			$(LIBFT_OBJ) $(MAND_OBJ)
					@$(CC) $(LIBFT_OBJ) $(MAND_OBJ) -o $(NAME)
					@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all:				$(NAME)

clean:
					@$(RM) $(MAND_OBJ)
					@$(RM) $(LIBFT_OBJ)
					@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:				clean
					@$(RM) $(NAME)
					@echo -e "$(RED)all deleted!$(DEFAULT)"

re:					fclean all

.PHONY:			all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m