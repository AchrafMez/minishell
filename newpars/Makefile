NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g -I./libft
LIBS = -L/Users/amezioun/.brew/opt/readline/lib -lreadline
INCLUDES = -I/Users/amezioun/.brew/opt/readline/include
LIBFT_SRCS = ./libft/ft_split.c ./libft/ft_itoa.c  ./libft/ft_strdup.c ./libft/ft_substr.c ./libft/ft_atoi.c ./libft/ft_strtrim.c ./libft/ft_strjoin.c \
./libft/ft_isalnum.c ./libft/ft_isalpha.c  ./libft/ft_isdigit.c ./libft/ft_strchr.c ./libft/ft_strlcpy.c \
./libft/ft_strlen.c ./libft/ft_strncmp.c ./libft/ft_strlcat.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c
SRCS = $(wildcard *.c)  ./tokenizer/tokenizer.c ./tokenizer/tokens_utils.c ./tokenizer/d_quotes.c ./tokenizer/s_quotes.c ./tokenizer/reds.c ./tokenizer/edit_tokens.c ./tokenizer/dollar.c ./tokenizer/special_chars.c ./parser/tokens_to_cmd.c ./parser/cmd_utils.c ./parser/free_cmd.c ./parser/check_syntax.c ./env/env_utils.c \
     ./env/set_env.c ./bata_exe/libc.c ./bata_exe/libft2.c ./bata_exe/libft3.c ./built_in/unset.c ./built_in/export.c ./built_in/env.c ./built_in/cd.c ./built_in/pwd.c  ./built_in/echo.c  ./built_in/exit.c  ./bata_exe/allocptr.c ./bata_exe/exec.c  ./bata_exe/handle_child.c ./bata_exe/cleaning.c ./execution/exec_builtin.c ./bata_exe/ft_heredoc.c   ./bata_exe/exec2.c ./bata_exe/exec3.c ./bata_exe/get_next_line.c ./bata_exe/handle_child2.c 
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o) 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): minishell.h $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_OBJS) $(LIBS) $(INCLUDES)

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME) libft.a

re: fclean all

.PHONY: all clean fclean re
