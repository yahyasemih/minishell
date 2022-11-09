NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = minishell.c \
	builtins/cd_builtin.c \
	builtins/env_builtin.c \
	builtins/pwd_builtin.c \
	builtins/echo_builtin.c \
	builtins/exit_builtin.c \
	builtins/unset_builtin.c \
	builtins/export_builtin.c \
	builtins/builtins_utils.c \
	environment/environment.c \
	environment/environment_utils.c \
	environment/env_variables_utils.c \
	execution/signals.c \
	execution/execution.c \
	execution/execution_utils.c \
	misc/str_split.c \
	misc/utilities.c \
	misc/string_utils.c \
	parsing/tokens.c \
	parsing/parsing.c \
	parsing/commands.c \
	parsing/parsing_utils.c \
	parsing/redirections_utils.c

INC = -I$(HOME)/.brew/Cellar/readline/8.2.1/include -Iincludes
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