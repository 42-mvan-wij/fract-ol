# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    utils.mk                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/16 16:38:25 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/03/16 17:42:27 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include libft/colours.mk

ifeq ($(shell uname),Linux)
IS_LINUX := 1
else
IS_LINUX :=
endif
ifeq ($(shell uname),Darwin)
IS_MAC := 1
else
IS_MAC :=
endif

print_prefix = printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(1)]" "$(2)"
exec_no_nl = printf "$(1)"; $(1)
