# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmota-ma <rmota-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 14:52:42 by dicosta-          #+#    #+#              #
#    Updated: 2025/06/25 18:04:07 by rmota-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name and compiler

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

EXTRAFLAGS = -lreadline -lncurses

# Sources and objects

LIBFT = includes/libft/libft.a

SRCS = main.c get_next_line.c get_next_line_utils.c

LEXER = init.c token.c custom_split.c custom_split_aux.c token_aux.c format_line.c

PARSER = parse.c syntax_aux.c syntax_check.c binary_tree.c

EXECUTER = commands.c commands2.c cmd_utils.c cmd_utils2.c cmd_utils3.c cmd_utils4.c cmd_utils5.c tree.c

SIGNALS = signals.c

EXPANDER = expand.c expander_check.c expander_check_aux.c

SRCS_DIR = srcs

LEXER_DIR = lexer

PARSER_DIR = parser

EXECUTER_DIR = execute

EXPANDER_DIR = expander

SIGNALS_DIR = signals

OBJS_DIR = objs

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

LEXER_OBJS = $(addprefix $(OBJS_DIR)/, $(LEXER:.c=.o))

PARSER_OBJS = $(addprefix $(OBJS_DIR)/, $(PARSER:.c=.o))

EXECUTER_OBJS = $(addprefix $(OBJS_DIR)/, $(EXECUTER:.c=.o))

SIGNALS_OBJS = $(addprefix $(OBJS_DIR)/, $(SIGNALS:.c=.o))

EXPANDER_OBJS = $(addprefix $(OBJS_DIR)/, $(EXPANDER:.c=.o))

# Colors

NO_COLOR = \033[0m

COLOR_RED = \033[1;31m

COLOR_GREEN = \033[1;32m

COLOR_PURPLE = \033[1;35m

COLOR_CYAN = \033[1;36m

# Messages

COMP_START = @echo "$(NO_COLOR)\nCompilation starting ...\n"

MINISHELL_OK = @echo "$(NO_COLOR)Minishell status: $(COLOR_GREEN)[OK]\n"

MINISHELL_KO = @echo "$(NO_COLOR)Minishell status: $(COLOR_RED)[KO]\n"

CLEAN_RUN = @echo "$(NO_COLOR)\nCleaning objects ...\n"

FCLEAN_RUN = @echo "$(NO_COLOR)\nCleaning objects and executables ...\n"

CLEAN_DONE = @echo "$(COLOR_GREEN)Clean complete!\n"

# Rules

all: $(NAME)
	
$(NAME): $(OBJS) $(EXPANDER_OBJS) $(EXECUTER_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(SIGNALS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(EXPANDER_OBJS) $(EXECUTER_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(SIGNALS_OBJS) $(LIBFT) $(EXTRAFLAGS) -o $(NAME)
	@$(MINISHELL_OK)
	
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(EXECUTER_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(EXPANDER_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(LEXER_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(PARSER_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/$(SIGNALS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@$(COMP_START)
	@make -C includes/libft -s

clean:
	@make clean -C includes/libft -s
	@rm -rf $(OBJS_DIR)
	@$(CLEAN_RUN)
	@$(CLEAN_DONE)
	@$(MINISHELL_KO)
	
fclean:
	@make fclean -C includes/libft -s
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@$(FCLEAN_RUN)
	@$(CLEAN_DONE)
	@$(MINISHELL_KO)

re: fclean all

r:
	@make re && clear && ./minishell

rv:
	@make re && clear && valgrind --leak-check=full ./minishell

gdb:
	@make re && gdb ./minishell

.PHONY: all clean fclean re