CC = cc
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g

RM = rm -rf  
HEADERS = builtin.h
# SRCS = ft_echo.c ft_export.c ft_pwd.c ft_cd.c ft_unset.c ft_env.c ft_exit.c ft_heredoc.c 
SRCS =main.c libft.c cleaning.c allocptr.c handle_child.c

NAME = minishell
OBJS = $(SRCS:.c=.o)
 LIBFT=#libft/libft.a


all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT)  $(OBJS) -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	@$(RM) $(OBJS) 
	@make clean -C libft

%.o : %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@ 

fclean : clean 
		@$(RM) $(NAME) 
		@make fclean -C libft

re : fclean all 

.PHONY: all clean fclean re 
