# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/28 14:05:04 by mvan-wij      #+#    #+#                  #
#    Updated: 2021/07/26 20:35:58 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fractol
LIBFT = libft/libft.a
ifeq ($(shell uname),Linux)
MINILIBX = minilibx-linux/libmlx.a
else
MINILIBX = minilibx_mms_20200219/libmlx.dylib
endif

CC = gcc
CFLAGS = -Wall -Wextra -Werror
ifdef DEBUG
CFLAGS += -g
endif

LIBS = -L$(dir $(LIBFT)) -lft -L$(dir $(MINILIBX)) -lmlx -lm
ifeq ($(shell uname),Linux)
LIBS += -lXext -lX11
else
LIBS += -framework OpenGL -framework AppKit
endif
HEADERS = libft/libft.h $(dir $(MINILIBX))/mlx.h src/constants.h src/defs.h
SOURCES = src/fractol.c src/mandelbrot_set.c src/julia_set.c src/hooks.c src/movement.c

ifdef BONUS
SOURCES += src/complex.c src/multibrot_set.c
HEADERS += src/bonus.h
CFLAGS  += -DBONUS=
LIBS    += -lpthread
endif

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%, $(SOURCES:c=o))
INCLUDES = $(addprefix -I,$(dir $(HEADERS)))

.PHONY: all clean fclean re debug bonus $(MINILIBX)

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

	@#cp $(LIBFT) $(NAME)
	@#ar -crs $(NAME) $(OBJECTS)

bonus:
	$(MAKE) BONUS=1

debug:
	$(MAKE) DEBUG=1

$(LIBFT): $(addprefix $(dir $(LIBFT)),$(shell $(MAKE) -s -C $(dir $(LIBFT)) sources))
ifdef DEBUG
	$(MAKE) -C $(dir $(LIBFT)) debug bonus
else
	$(MAKE) -C $(dir $(LIBFT)) bonus
endif

$(MINILIBX):
	$(MAKE) -C $(dir $(MINILIBX))
ifeq ($(shell uname),Darwin)
	cp $(MINILIBX) $(notdir $(MINILIBX))
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	rm -rf $(OBJDIR)
	rm -f $(NAME)

re: fclean all
