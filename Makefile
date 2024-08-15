NAME = cub3d

CC = cc

CFLAGS =  -g -Wall -Werror -Wextra -Wunreachable-code -Ofast
LDFLAGS = -pthread -lm
OBJ_DIR = obj/
SRC_DIR = src/

GL_FLAG		=	-lglfw -L
GL_PATH		=	/Users/$(USER)/.brew/opt/glfw/lib/

SRC		:=	main.c \
			get_next_line.c \
			parse.c \
			parse_utils.c \
			parse_utils2.c \
			render.c \
			render_utils.c \
			render_utils2.c \
			utils.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
HEADER = -I ./include -I ./lib/MLX42/include/MLX42/

LIBFT = ./libft/libft.a

LIBMLX42 = "./lib/MLX42/build/libmlx42.a"

LIBGLFW = "./lib/glfw-3.3.8.bin.MACOS/lib-x86_64/libglfw3.a"

FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(HEADER) $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	cd libft && make
	mkdir lib && cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	cd lib/MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(LIBMLX42) $(LIBFT) $(FRAMEWORK) $(OBJS) ${GL_FLAG} ${GL_PATH} -o $(NAME)
	# $(CC) $(LDFLAGS) $(CFLAGS) $(LIBMLX42) $(LIBGLFW) $(LIBFT) $(FRAMEWORK) $(OBJS) -o $(NAME)

install_brew:
	@echo "----- installing brew -----"
	rm -rf $HOME/.brew && rm -rf $HOME/goinfre/.brew && \
	git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && \
	echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && \
	source $HOME/.zshrc && brew update

install_glfw:
	@echo "----- installing glfw -----"
	brew install glfw

install: install_brew install_glfw

clean:
	cd libft && make clean
	rm -rf $(OBJ_DIR)
	rm -rf ./lib
	clear

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)
	clear

re: fclean all

.PHONY: all clean fclean re libft
