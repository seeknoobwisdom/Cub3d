# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRCDIR = src
INCDIR = include

# Subdirectories with C files
SRC_EXE = $(SRCDIR)/execution
SRC_PARC = $(SRCDIR)/parcing

# Source files
SRCS =	main.c error.c \
		$(SRC_EXE)/configur_mlx.c  \
		$(SRC_EXE)/utils.c \
		$(SRC_EXE)/game_loop.c \
		$(SRC_EXE)/configur_player.c  \
		$(SRC_EXE)/reneder_scene.c\
		$(SRC_EXE)/exec.c \
    	$(SRC_PARC)/parce.c \
		$(SRC_PARC)/check_map.c \
		$(SRC_PARC)/fill_info.c \
		$(SRC_PARC)/test.c \
		$(SRC_PARC)/utils.c \
		$(SRC_PARC)/Normlize.c \
		$(SRC_PARC)/check_files.c \



# Object files
OBJS = $(SRCS:.c=.o)

# Executable
NAME = cub3d

UNAME_S := $(shell uname -s)

LINUX = -Lminilibx-linux -lmlx -lXext -lX11 -lm

MACOS = -Lminilibx -lmlx -framework OpenGL -framework AppKit

ifeq ($(UNAME_S),Linux)
    FLAGS = $(LINUX)
endif

ifeq ($(UNAME_S),Darwin)
    FLAGS = $(MACOS) 
endif


# Default target
#minix // remove for test valgrind
all: dirs minix $(NAME)

# Create directories
dirs:
	mkdir -p $(INCDIR) $(SRCDIR) $(SRC_EXE) $(SRC_PARC)

# add 
minix:
	make -C minilibx-linux
ft:
	make -C libft

#-Lminilibx -lmlx -framework OpenGL -framework AppKit // remove it to text valgrind
$(NAME): $(OBJS) minilibx minilibx-linux ft
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft $(FLAGS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -Llibft -lft $(FLAGS) -I $(INCDIR) -c $< -o $@

clean:
	cd libft && make fclean
	cd minilibx && make clean
	cd minilibx-linux && make clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(VALG)

re: fclean all

.PHONY: all clean fclean re dirs