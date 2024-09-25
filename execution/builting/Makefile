CC = cc
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g

RM = rm -rf  
HEADERS = builtin.h
SRCS = ft_echo.c ft_export.c ft_pwd.c


NAME = minishell
OBJS = $(SRCS:.c=.o)
LIBFT=libft/libft.a


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
