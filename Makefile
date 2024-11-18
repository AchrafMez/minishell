CC = cc
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g

RM = rm -rf  
HEADERS = builtin.h
# SRCS = ft_echo.c ft_export.c ft_pwd.c ft_cd.c ft_unset.c ft_env.c ft_exit.c ft_heredoc.c 
SRCS =main.c libft.c cleaning.c allocptr.c handle_child.c ft_pwd.c ft_cd.c ft_echo.c #ft_env.c ft_exit.c ft_export.c ft_unset.c
NAME = minishell
OBJS = $(SRCS:.c=.o)



all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)


clean:
	@$(RM) $(OBJS) 


%.o : %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@ 

fclean : clean 
		@$(RM) $(NAME) 


re : fclean all 

.PHONY: all clean fclean re 
