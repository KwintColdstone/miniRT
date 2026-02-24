.DEFAULT_GOAL := all

NAME	=	minirt

CFILES	=	main.c\
			$(PARSE_CFILES)\
			camera.c\
			hit_cylinder.c\
			hit_objects.c\
			init.c\
			material.c\
			ray.c\
			render.c\
			transform.c\
			utils.c\
			vec3.c\
			display.c\
			world_hit.c

PARSE_CFILES =	parse.c\
				count_objects.c\
				parse_utils.c

OFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.o))
DEPFILES	= $(addprefix $(BUILDDIR),$(CFILES:.c=.d))

VPATH	= $(INCLUDE) $(SRCDIRS)
BUILDDIR = build/
SRCDIR = src/
INCDIR = inc/
LIBDIR = lib/
SRCDIRS =	$(SRCDIR) \
			$(addprefix $(SRCDIR), parsing display)

$(SRCDIR):
	mkdir -p $@
$(INCDIR):
	mkdir -p $@
$(BUILDDIR):
	mkdir -p $@
$(LIBDIR):
	mkdir -p $@

#libraries
LDFLAGS	= -L$(LIBDIR) -lm
LIBFTDIR	= $(LIBDIR)libft/
LIBFT	= $(LIBFTDIR)libft.a

MLXDIR = $(LIBDIR)mlx42/
MLXFILE = $(MLXDIR)build/libmlx42.a
MLX	= -L$(MLXDIR)/build/ -lmlx42 -ldl -lglfw -pthread -lm

INCLUDE = $(INCDIR) $(LIBFTDIR) $(MLXDIR)/include

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
#CFLAGS	=
CFLAGS	= -Wall -Wextra -Werror
#CFLAGS	= -Wall -Wextra -Werror -fsanitize=undefined
INPUT	= rt_files/cyl.rt


-include $(OFILES:.o=.d)

# builds .d files, then builds .o files based on .d.
# skips files that weren't changed (see CPPFLAGS)
$(LIBFT):
	$(MAKE) all -C $(LIBFTDIR)

$(MLXFILE):
	$(MAKE) mlx_build

$(BUILDDIR)%.o: %.c $(INCLUDE) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OFILES) $(MLXFILE)
	$(CC) $(CFLAGS) -o $@ $(OFILES) $(LIBFT) $(MLX) $(LDFLAGS) $(INCFLAGS)

#Base/project requirements
all: $(NAME)
mlx_build:
	mkdir -p $(MLXDIR) ; cd $(MLXDIR) ;\
	cmake -B build ; cmake --build build  -j4
	chmod 777 $(MLXDIR)/build/libmlx42.a
libs_clean:
	$(RM) $(MLXDIR)/build ; $(MAKE) fclean -C $(LIBFTDIR)
clean:
	$(RM) $(OFILES)
fclean:	clean libs_clean
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
