# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/16 16:35:47 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/03/17 17:36:28 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

include utils.mk

################################################################################

PROJECT		:= fract-ol
NAME		:= fractol
NAME_BONUS	:= fractol

LIBFT		:= libft/libft.a
MINILIBX	:= $(if $(IS_LINUX), minilibx-linux/libmlx.a, minilibx_mms_20200219/libmlx.dylib)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror $(if $(DEBUG), -g3) $(if $(SANITIZE), -fsanitize=address -g3)

################################################################################

USER_LIBS += $(LIBFT) $(MINILIBX)
SYSTEM_LIBS += m $(if $(IS_LINUX), X11 Xext)
FRAMEWORKS += $(if $(IS_MAC), OpenGL AppKit)
HEADERS :=						\
	libft/libft.h				\
	$(dir $(MINILIBX))/mlx.h	\
	src/constants.h				\
	src/defs.h
SOURCES :=					\
	src/fractol.c			\
	src/mandelbrot_set.c	\
	src/julia_set.c			\
	src/hooks.c				\
	src/movement.c			\
	src/draw.c				\
	src/bonus.c

################################################################################

ifdef BONUS
NAME	:= $(NAME_BONUS)
HEADERS +=				\
	src/bonus.h
SOURCES	+=				\
	src/complex.c		\
	src/multibrot_set.c
CFLAGS	+= -DBONUS
endif

################################################################################

OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))
INCLUDE_FLAGS += $(addprefix -I, $(sort $(dir $(HEADERS))))
LIB_FLAGS += $(addprefix -L, $(sort $(dir $(USER_LIBS)))) $(addprefix -l, $(SYSTEM_LIBS) $(patsubst lib%,%,$(basename $(notdir $(USER_LIBS))))) $(addprefix -framework , $(FRAMEWORKS))

export CFLAGS := $(sort $(CFLAGS))
export LIB_FLAGS := $(LIB_FLAGS)

DATA_FILE := .make_data.txt
MAKE_DATA := $(CFLAGS) $(LIB_FLAGS) $(INCLUDE_FLAGS) $(sort $(OBJECTS))
ifneq ($(shell echo $(MAKE_DATA)), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES := clean
endif

################################################################################

all: $(PRE_RULES) $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	@$(call print_prefix,"$(PROJECT)","make")
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_FLAGS) $(LIB_FLAGS) -o $(NAME)
	@$(call print_prefix,"$(PROJECT)","make")
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

	@echo $(MAKE_DATA) > $(DATA_FILE)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(call print_prefix,"$(PROJECT)","make")
	@$(call exec_no_nl,$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(INCLUDES) -c $< -o $@)
	@printf "$(CLEAR_REST_OF_LINE)\r"

$(LIBFT): $(addprefix $(dir $(LIBFT)), $(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
	@$(MAKE) SILENT=1 -C $(dir $(LIBFT))

ifeq ($(IS_LINUX),1)
$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
else
$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
	cp $(MINILIBX) .
endif

bonus:
	@$(MAKE) BONUS=1

debug:
	@$(MAKE) DEBUG=1

clean:
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean: clean
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(NAME)
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(DATA_FILE)
	@$(MAKE) -C $(dir $(LIBFT)) fclean

re: fclean all

.PHONY: all bonus debug clean fclean re

################################################################################
