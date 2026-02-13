.DEFAULT_GOAL := all

NAME	=	durak

CFILES	=	main.c\
			test.c\
			init.c\
			deck_manip.c\
			game_start.c\
			printing.c

OFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.o))
DEPFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.d))

VPATH	= $(INCLUDE) $(SRCDIRS)
BUILDDIR = build/
SRCDIR = src/
INCDIR = inc/
SRCDIRS = $(SRCDIR)\
		  $(addprefix $(SRCDIR), interface deck_manipulation)
$(SRCDIR):
	mkdir -p $@
$(INCDIR):
	mkdir -p $@
$(BUILDDIR):
	mkdir -p $@

INCLUDE = $(INCDIR)

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
CFLAGS	= -Wall -Wextra -Werror
#CFLAGS	= -Wall -Wextra -Werror -fsanitize=undefined
LDFLAGS	=
INPUT	=


-include $(OFILES:.o=.d)

# builds .d files, then builds .o files based on .d.
# skips files that weren't changed (see CPPFLAGS)
$(BUILDDIR)%.o: %.c $(INCLUDE) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $@ $(OFILES) $(LDFLAGS) $(INCFLAGS)

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
