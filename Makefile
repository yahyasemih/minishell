NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
	tokens.c \
	parsing.c \
	utilities.c \
	commands.c \
	signals.c \
	execution.c \
	cd_builtin.c \
	env_builtin.c \
	pwd_builtin.c \
	echo_builtin.c \
	exit_builtin.c \
	unset_builtin.c \
	export_builtin.c \
	environment.c \
	string_utils.c \
	parsing_utils.c \
	builtins_utils.c \
	execution_utils.c \
	environment_utils.c \
	env_variables_utils.c \
	redirections_utils.c

INC = -I$(HOME)/.brew/Cellar/readline/8.2.1/include
LIB = -L$(HOME)/.brew/Cellar/readline/8.2.1/lib

DEPS = $(patsubst %.c,%.d,$(SRCS))
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
RED = \033[1;31m
GREEN = \033[1;32m
NC = \033[1;0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(RED)Compiling $(NAME)...$(NC)"
	@echo "$(RED)Linking...$(NC)"
	@$(CC) $(OBJECTS) -o $(NAME) $(LIB) -lreadline
	@echo "$(GREEN)Finished linking && compiling...$(NC)"

clean:
	@echo "$(RED)Cleaning objects...$(NC)"
	@rm -rf $(OBJECTS)
	@echo "$(GREEN)Cleaned objects...$(NC)"
	@echo "$(RED)Cleaning dependencies...$(NC)"
	@rm -rf $(DEPS)
	@echo "$(GREEN)Cleaned dependencies...$(NC)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@echo "$(GREEN)Cleaned $(NAME)...$(NC)"

re: fclean all

.PHONY: clean fclean all re

-include $(DEPS)

%.c:

%.o: %.c Makefile
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@echo "$(RED)Compiling $< ...$(NC)"