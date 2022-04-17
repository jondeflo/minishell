NAME = minishell

SRC_DIR = srcs/
OBJ_DIR = obj/
INC_DIR = includes/
LIB_DIR = libft/

INCLUDES = -I$(INC_DIR)

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
LIBFT_FLAGS = -L $(LIB_DIR) -lft
MMD = -MMD

SRC_DIR_P = $(SRC_DIR)parser/
FILES_P = checks.c\
		env.c\
		env_utils.c\
		flag.c\
		in_out.c\
		norme.c\
		read_line.c\
		parce.c\
		parce_init.c\
		parce2.c\
		parcer_utils.c\
		pipe_spliter.c\
		redirect.c\
		remove.c\
		remove_cases.c\
		remove_check.c\
		remove_utils.c\
		replace_utils.c\
		shell.c\
		skipper.c\
		splitter.c\
		splitter_utils.c\

SRC_DIR_B = $(SRC_DIR)buildin/
FILES_B = build_in.c\
		cd.c\
		exec.c\
		exec_norme.c\
		exec_utils.c\
		export.c\
		fn.c\
		list.c\
		minishell.c\
		path.c\
		path_error.c\
		pwd.c\
		unset.c\
		sig_handler.c\
		main.c\

FILES = $(addprefix $(SRC_DIR_P), $(FILES_P))
FILES += $(addprefix $(SRC_DIR_B), $(FILES_B))

OBJ_FILES = $(FILES_P:.c=.o)
OBJ_FILES += $(FILES_B:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(OBJ_DIR) $(NAME)

$(NAME): libft $(OBJ)
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJ) $(LIBFT_FLAGS)

libft:
	make -C $(LIB_DIR)

-include $(OBJ:.o=.d)

$(OBJ_DIR)%.o: $(SRC_DIR_P)%.c
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) $(MMD) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR_B)%.c
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) $(MMD) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_FILES)
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

run: re
	./minishell

re: fclean all

.PHONY: libft