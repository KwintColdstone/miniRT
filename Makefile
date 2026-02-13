.DEFAULT_GOAL := all

NAME	=	minirt

CFILES	=	main.c\
			camera.c\
			hit_cylinder.c\
			hit_objects.c\
			init.c\
			material.c\
			parse.c\
			parse_utils.c\
			ray.c\
			render.c\
			transform.c\
			utils.c\
			vec3.c\
			world_hit.c

OFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.o))
DEPFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.d))

VPATH	= $(INCLUDE) $(SRCDIRS)
BUILDDIR = build/
SRCDIR = src/
INCDIR = inc/
LIBDIR = lib/
SRCDIRS = $(SRCDIR)\
		  $(addprefix $(SRCDIR), interface deck_manipulation)
$(SRCDIR):
	mkdir -p $@
$(INCDIR):
	mkdir -p $@
$(BUILDDIR):
	mkdir -p $@
$(LIBDIR):
	mkdir -p $@

INCLUDE = $(INCDIR) $(LIBFTDIR)

RM	= rm -rf
CC	= cc

# this apparently achieves dependency gen on per-file basis, on compilation
# without relying on hacky solutions like the one on GNU Makefile docs
# -MMD is a combination of a few flags:
#  -M generates dependency files
#  -MD is the same as -M -MF file
#  -MF file specifies file to write dependencies to
#  -MP adds a phony target so make does not cry when a .h file is removed
CPPFLAGS	= $(INCFLAGS) -MMD -MP

INCFLAGS	= $(addprefix -I,$(INCLUDE))
CFLAGS	=
#CFLAGS	= -Wall -Wextra -Werror
#CFLAGS	= -Wall -Wextra -Werror -fsanitize=undefined
LDFLAGS	= -L$(LIBDIR)
LIBFTDIR	= $(LIBDIR)libft/
LIBFT	= $(LIBFTDIR)libft.a
INPUT	=


-include $(OFILES:.o=.d)

# builds .d files, then builds .o files based on .d.
# skips files that weren't changed (see CPPFLAGS)
$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)

$(BUILDDIR)%.o: %.c $(INCLUDE) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(CFLAGS) -o $@ $(OFILES) $(LIBFT) $(LDFLAGS) $(INCFLAGS)

#Base/project requirements
all: $(NAME)
#libs_clean:
#	$(MAKE) fclean -C $(LIBFT_DIR)
clean:
	$(RM) $(OFILES)
fclean:	clean #libs_clean
	$(RM) $(NAME) $(DEPFILES)
re:	fclean all

#LSP connection for neovim
clangd:
	$(MAKE) fclean
	intercept-build-14 $(MAKE)
bear:
	$(MAKE) fclean
	bear -- $(MAKE)

#debugging
debug: CFLAGS += -g
debug: clean $(NAME)
gdb: fclean debug
	gdb -tui ./$(NAME)
test: $(NAME)
	$(MAKE) -s run
run:
	./$(NAME) $(INPUT)
leak:
	$(MAKE) -s debug
	valgrind --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./$(NAME) $(INPUT)
val:
	valgrind --track-fds=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all ./$(NAME) $(INPUT)

.PHONY:	clangd all clean fclean re test run leak debug gdb
