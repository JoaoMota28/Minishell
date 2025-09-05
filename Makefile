### COLOURS ###
PINK 	= \e[1;35m
PURPLE	= \e[0;95m
WHITE   = \e[1;37m
DEFAULT = \e[0m

### VARIABLES ###
NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
INCLUDE			= -I inc/

### MINISHELL SRCS ###
SRCS	 		= $(LEXER_SRCS) $(EXP_SRCS) $(PARSER_SRCS) $(BUILTIN_SRCS) $(EXEC_SRCS) minishell.c inits.c utils.c exit_free.c handler.c signals.c
SRC_PATH		= src/

LEXER_SRCS		= errors_free.c lexer.c syntax_checker.c subshell_syntax.c set_types.c set_token_types.c
LEXER_PATH 		= src/lexer/
LEXER			= $(addprefix $(LEXER_PATH), $(LEXER_SRCS))

EXP_SRCS		= expander.c expand_token.c expanded_len.c
EXP_PATH		= src/expander/
EXP				= $(addprefix $(EXP_PATH), $(EXP_SRCS))

PARSER_SRCS		= parser.c tree_utils.c
PARSER_PATH		= src/parser/
PARSER			= $(addprefix $(PARSER_PATH), $(PARSER_SRCS))

BUILTIN_SRCS	= builtin_utils.c echo_builtin.c pwd_builtin.c env_builtin.c cd_builtin.c exit_builtin.c unset_builtin.c export_builtin.c builtins.c
BUILTIN_PATH	= src/executor/builtins
BUILTIN			= $(addprefix $(BUILTIN_PATH), $(BUILTIN_SRCS))

EXEC_SRCS		= executor.c exec.c exec_utils.c redirections.c pipes.c and_or.c heredoc.c redir_cmd.c subshell.c shlvl.c
EXEC_PATH		= src/executor
EXEC			= $(addprefix $(EXEC_PATH), $(EXEC_SRCS))

TOTAL_SRCS		= $(words $(SRCS))
FILES			= 0

### OBJECTS ###
OBJS_PATH		= obj/
OBJS 			= $(SRCS:%.c=$(OBJS_PATH)%.o)
ALL_OBJ			= $(OBJS_PATH)*.o

### COMPLETE LIB ###
LIBFT_PATH		= complete_lib/42_Libft/
LIBFT			= $(LIBFT_PATH)libft.a
FT_PRINTF_PATH	= complete_lib/42_Printf/
FT_PRINTF		= $(FT_PRINTF_PATH)libftprintf.a
GNL_PATH		= complete_lib/42_GNL/
GNL				= $(GNL_PATH)libgnl.a
PERSONAL_LIBS	= -lft -lgnl -lftprintf

vpath %.c $(SRC_PATH) $(PARSER_PATH) $(LEXER_PATH) $(EXP_PATH) $(BUILTIN_PATH) $(EXEC_PATH)

### RULES ###
all: 			$(NAME)

$(OBJS_PATH)%.o: %.c | $(OBJS_PATH)
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ && \
				$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
				$(call PRINT_PROGRESS, $(TOTAL_SRCS),$(PINK), $(WHITE)Compiling$(DEFAULT) $@)

$(OBJS_PATH):
				@mkdir -p $@

$(NAME): 		$(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL) $(OBJS_PATH)
				@echo "$(WHITE)Bringing $(PINK)$(NAME)$(WHITE) to life!$(DEFAULT)"
				@echo "$(WHITE)Creating $(PINK)$(NAME)'s$(WHITE) executable...$(DEFAULT)"
				@$(CC) $(CFLAGS) $(OBJS) -lreadline -L$(LIBFT_PATH) -L$(FT_PRINTF_PATH) \
				-L$(GNL_PATH) $(PERSONAL_LIBS) -o $@
				@echo "$(PINK)$(NAME) was born!$(DEFAULT)"

### MAKE LIB ###
$(LIBFT):
				@make -s -C $(LIBFT_PATH)

$(FT_PRINTF):
				@make -s -C $(FT_PRINTF_PATH)

$(GNL):
				@make -s -C $(GNL_PATH)

### CLEAN RULES ###
clean:
				@make -s -C $(LIBFT_PATH) clean
				@make -s -C $(FT_PRINTF_PATH) clean
				@make -s -C $(GNL_PATH) clean
				@rm -rf $(OBJS)
				@rm -rf obj
				@echo "$(WHITE)✩°｡⋆ $(PINK)Files Cleaned$(WHITE) ⋆｡°✩ \n \
	(\ (\    \n \
( ~_•)    \n \
(っ▄︻▇〓▄︻┻┳═ ─ ҉.  \n \
 /　 )  / \    \n \
(/￣∪  /   \ $(DEFAULT)"

fclean: 		clean
				@make -s -C $(LIBFT_PATH) fclean
				@make -s -C $(FT_PRINTF_PATH) fclean
				@make -s -C $(GNL_PATH) fclean
				@rm -f $(NAME)
				@echo "$(WHITE)⋆˚࿔ Executable Killed˚⋆♡$(DEFAULT)"

re: 			fclean all

v:				$(NAME)
				clear && valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --track-origins=yes --suppressions=readline.supp ./minishell

ch:				$(NAME)
				valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

.PHONY: 		all clean fclean re v ch

define PRINT_PROGRESS
    if [ "$(FILES)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi	
endef
