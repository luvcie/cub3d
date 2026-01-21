NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -g

SRC_DIR = src
INC_DIR = include

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/create_window.c \
       $(SRC_DIR)/drawing.c \
       $(SRC_DIR)/keybinds.c

OBJS = $(SRCS:.c=.o)

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

# cache nix paths to avoid slow find on every make
NIX_CACHE := .nix_paths
$(shell if [ ! -f $(NIX_CACHE) ] && [ -d /nix/store ]; then \
	echo "X11_LIB=$$(find /nix/store -name 'libX11.so.6.4.0' 2>/dev/null | xargs -I{} sh -c 'file {} | grep -q 64-bit && dirname {}' 2>/dev/null | head -1)" > $(NIX_CACHE); \
	echo "XEXT_LIB=$$(find /nix/store -name 'libXext.so.6*' 2>/dev/null | xargs -I{} sh -c 'file {} | grep -q 64-bit && dirname {}' 2>/dev/null | head -1)" >> $(NIX_CACHE); \
fi)
-include $(NIX_CACHE)

MLX_FLAGS = -L$(MLX_PATH) -lmlx -L$(X11_LIB) -L$(XEXT_LIB) -lXext -lX11 -lm

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I$(LIBFT_PATH)

INC = -I$(MLX_PATH) $(LIBFT_INC) -I$(INC_DIR)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX_PATH):
	@if [ ! -f $(MLX_PATH)/Makefile ]; then \
		rm -rf $(MLX_PATH); \
		git clone https://github.com/42Paris/minilibx-linux $(MLX_PATH); \
		./patch_minilibx.sh; \
	fi

$(MLX): $(MLX_PATH)
	make -C $(MLX_PATH)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(MLX_FLAGS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)
	@if [ -d $(MLX_PATH) ] && [ -f $(MLX_PATH)/Makefile.gen ]; then \
		make -C $(MLX_PATH) clean 2>/dev/null || true; \
	fi
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)
	make -C $(LIBFT_PATH) fclean

re: fclean all

bonus: all

TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/test_movement.c \
            $(SRC_DIR)/keybinds.c \
            $(SRC_DIR)/drawing.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_NAME = test_movement

test: $(LIBFT) $(MLX) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L$(LIBFT_PATH) -lft $(MLX_FLAGS) -o $(TEST_NAME)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

testclean:
	rm -f $(TEST_OBJS) $(TEST_NAME)

.PHONY: all clean fclean re bonus test testclean
