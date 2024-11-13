NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft
LDFLAGS = -lreadline
SRCS = $(wildcard *.c) ./tokenizer/tokenizer.c ./tokenizer/tokens_utils.c ./tokenizer/d_quotes.c ./tokenizer/s_quotes.c ./tokenizer/reds.c ./tokenizer/edit_tokens.c ./tokenizer/dollar.c ./tokenizer/special_chars.c ./parser/tokens_to_cmd.c ./parser/cmd_utils.c ./parser/free_cmd.c
LIBFT = ./libft/libft.a
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): minishell.h $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re