NAME = train_shell 
CC = cc -Wall -Wextra -Werror -Iincludes -Its_readline/includes
CCDEBUG = $(CC) -g3 -O0

SRC_DIR = src
SRC_FILES = aliasing.c \
			builtin_handling.c \
			cleaning.c \
			exec.c \
			get_command_binary_path.c \
			get_paths.c \
			get_redirections.c \
			heredoc.c \
			init_env.c \
			is_token_type.c \
			lexer.c \
			list_to_array.c \
			main.c \
			main_loop.c \
			parser.c \
			parsing.c \
			print_nodes.c \
			quote_trim.c \
			separator_token.c \
			set_token_types.c \
			setup_redirections.c \
			syntax.c \
			tok_to_args.c \
			ts_alias.c \
			ts_cd.c \
			ts_echo.c \
			ts_exit.c \
			word_token.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ ts_readline.a

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

debug: fclean
	$(MAKE) CC="$(CCDEBUG)" all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all debug clean fclean re
