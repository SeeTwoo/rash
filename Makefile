NAME = tshoo 
CC = cc -Wall -Wextra -Werror -Iincludes
CCDEBUG = $(CC) -g3 -O0

SRC_DIR = src
SRC_FILES = aliasing.c \
			assign_variable.c \
			build_prompt.c \
			builtin_handling.c \
			cleaning.c \
			environment_manipulation.c \
			exec.c \
			exec_config_file.c \
			expansion.c \
			get_bin_path.c \
			get_next_line.c \
			get_redirections.c \
			heredoc.c \
			init_env.c \
			is_token_type.c \
			lexer.c \
			list_to_array.c \
			loops.c \
			main.c \
			parser.c \
			parsing.c \
			print_nodes.c \
			separator_token.c \
			set_token_types.c \
			setup_redirections.c \
			syntax.c \
			tok_to_args.c \
			trim_command.c \
			ts_alias.c \
			ts_cd.c \
			ts_echo.c \
			ts_env.c \
			ts_exit.c \
			ts_unalias.c \
			ts_unset.c \
			word_token.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ libs/key_value.a libs/tshoo_line.a

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
