cmake_minimum_required(VERSION 3.23)
project(minishell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g -fsanitize=address")
include_directories(~/.brew/Cellar/readline/8.2.1/include)
link_directories(~/.brew/Cellar/readline/8.2.1/lib)
add_executable(minishell minishell.c minishell.h tokens.c tokens.h parsing.c parsing.h parsing_utils.c parsing_utils.h utilities.c utilities.h commands.c commands.h string_utils.c string_utils.h redirections_utils.c redirections_utils.h signals.c signals.h execution.c execution.h builtins_utils.c builtins_utils.h execution_utils.c execution_utils.h env_variables_utils.c env_variables_utils.h cd_builtin.c builtins.h echo_builtin.c pwd_builtin.c exit_builtin.c unset_builtin.c export_builtin.c env_builtin.c)
target_link_libraries(minishell readline)
