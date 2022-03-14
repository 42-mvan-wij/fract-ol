# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/29 11:08:18 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/03/14 17:25:53 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

PROJECT		= fractol
NAME		= fractol
NAME_BONUS	= fractol
LIBFT		= libft/libft.a
ifeq ($(shell uname),Linux)
MINILIBX	= minilibx-linux/libmlx.a
else
MINILIBX	= minilibx_mms_20200219/libmlx.dylib
endif

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
ifndef NO_SANITIZE
CFLAGS	+= -fsanitize=address
endif
ifdef DEBUG
CFLAGS	+= -g
endif
DATA_FILE := .make_data.txt

# Common
LIBS	= -L$(dir $(LIBFT)) -lft -L$(dir $(MINILIBX)) -lmlx -lm
HEADERS = libft/libft.h $(dir $(MINILIBX))/mlx.h src/constants.h src/defs.h
SOURCES = src/fractol.c src/mandelbrot_set.c src/julia_set.c src/hooks.c src/movement.c src/draw.c src/bonus.c

ifndef BONUS
SOURCES	+=
HEADERS	+=
CFLAGS	+=
LIBS	+=
else
NAME	= $(NAME_BONUS)
SOURCES += src/complex.c src/multibrot_set.c
HEADERS += src/bonus.h
CFLAGS  += -DBONUS
LIBS    +=
endif
ifeq ($(shell uname),Linux)
LIBS	+= -lXext -lX11
else
LIBS	+= -framework OpenGL -framework AppKit
endif

include $(dir $(LIBFT))/colours.mk
RULE_SPACING	= 6
PROJECT_SPACING	= 11

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(sort $(addprefix -I,$(dir $(HEADERS))))

PRE_RULES	:=
ifneq ($(shell echo "$(CFLAGS)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES	+= clean
endif

print_prefix = printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(1)]" "$(2)"

.PHONY: all clean fclean re debug bonus

all: $(PRE_RULES) $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	@$(call print_prefix,"$(PROJECT)","make")
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@$(call print_prefix,"$(PROJECT)","make")
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"
	@echo "$(CFLAGS)" > $(DATA_FILE)

bonus:
	@$(MAKE) BONUS=1

debug:
	@$(MAKE) DEBUG=1

$(LIBFT): $(addprefix $(dir $(LIBFT)),$(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
ifdef DEBUG
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT)) debug
else
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT))
endif

$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
ifeq ($(shell uname),Darwin)
	cp $(MINILIBX) $(notdir $(MINILIBX))
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(call print_prefix,"$(PROJECT)","make")
	@printf "$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@$(CLEAR_REST_OF_LINE)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(NAME)
	@$(MAKE) -C $(dir $(LIBFT)) fclean

re: fclean all
