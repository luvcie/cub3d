# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 15:03:18 by pramos-c          #+#    #+#              #
#    Updated: 2026/02/03 13:05:42 by lucpardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -g

SRC_DIR = src
INC_DIR = include

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/input/create_window.c \
       $(SRC_DIR)/input/keybinds.c \
       $(SRC_DIR)/input/movement.c \
       $(SRC_DIR)/render/drawing.c \
       $(SRC_DIR)/render/help_menu.c \
       $(SRC_DIR)/render/minimap.c \
       $(SRC_DIR)/render/ray_minimap.c \
       $(SRC_DIR)/render/ray_minimap_cast.c \
       $(SRC_DIR)/render/raycasting.c \
       $(SRC_DIR)/render/render_3d.c \
       $(SRC_DIR)/render/textures.c \
       $(SRC_DIR)/render/wall_calc.c \
       $(SRC_DIR)/render/aa_utils.c \
       $(SRC_DIR)/render/aa_line.c \
       $(SRC_DIR)/render/aa_circle.c \
       $(SRC_DIR)/parsing/get_next_line.c \
       $(SRC_DIR)/parsing/parse_map.c \
       $(SRC_DIR)/parsing/parse_config.c \
       $(SRC_DIR)/parsing/validate_map.c \
       $(SRC_DIR)/parsing/validate_walls.c \
       $(SRC_DIR)/parsing/free_game.c \
       $(SRC_DIR)/parsing/utils.c

OBJS = $(SRCS:.c=.o)
HDRS = $(INC_DIR)/cub3d.h

# animation state files
TOTAL_FILES := $(words $(SRCS))
SPINNER_FILE := .spinner_state
COUNTER_FILE := .compile_counter

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
	@make -C $(LIBFT_PATH) --no-print-directory

$(MLX_PATH):
	@if [ ! -f $(MLX_PATH)/Makefile ]; then \
		printf "\033[1;36m[ 1/ 1]\033[0m Cloning minilibx...                        [\033[1;33m-\033[0m]"; \
		rm -rf $(MLX_PATH); \
		git clone -q https://github.com/42Paris/minilibx-linux $(MLX_PATH) 2>/dev/null; \
		./patch_minilibx.sh > /dev/null 2>&1; \
		printf "\r\033[K\033[1;32m[ 1/ 1] ✓ minilibx cloned\033[0m\n"; \
	fi

$(MLX): $(MLX_PATH)
	@printf "\033[1;36m[31/31]\033[0m Building minilibx...                       [\033[1;33m-\033[0m]"
	@make -C $(MLX_PATH) > /dev/null 2>&1
	@printf "\r\033[K\033[1;32m[31/31] ✓ minilibx built\033[0m\n"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@printf "\r\033[K\033[1;32m[%2d/%2d] ✓ Compiled all files\033[0m\n" "$(TOTAL_FILES)" "$(TOTAL_FILES)"
	@rm -f $(SPINNER_FILE) $(COUNTER_FILE)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "+-----------------------------------------------------------------------------+"
	@echo "| |       |\\                                           -~ /     \\  /          |"
	@echo "|~~__     | \\                                         | \\/       /\\          /|"
	@echo "|    --   |  \\                                        | / \\    /    \\     /   |"
	@echo "|      |~_|   \\                                       |/    \\/         /      |"
	@echo "|--__  |   -- |\\______________________________________|    /  \\     /     \\   |"
	@echo "|   |~~--__  |~_|____|____|____|____|____|____|_______|\\  /     \\/          \\/|"
	@echo "|   |      |~--_|__|____|____|____|____|____|____|____|/ \\    /   \\       /   |"
	@echo "|___|______|__|_||____|____|____|____|____|______|____|    \\/       \\  /      |"
	@echo "|        :   | _|___|____|____|____|____|____|___|____|/  \\      /       \\    |"
	@echo "|        :_--~~ |_|____|____|____|____|____|____|_____|\\/      \\ /         \\  |"
	@echo "|  __--  :  |  /                                      | \\     /  \\          /\\|"
	@echo "|~~  |   :  | /                                       |  \\  /      \\      /   |"
	@echo "|    |      |/                                        |  /\\          \\  /     |"
	@echo "|    |      /                                         |/   \\          /\\      |"
	@echo "|    |     /                                           -_   \\       /    \\    |"
	@echo "+-----------------------------------------------------------------------------+"
	@echo "|          |          |  2  3  4  | /~~~~~\\ |             |_| ....  ......... |"
	@echo "|   1337   |    42 %  |           | | ~J~ | |     93 %    |_| ....  ......... |"
	@echo "|   AMMO   |  HEALTH  |  5  6  7  |  \\===/  |    ARMOR    |#| ....  ......... |"
	@echo "+-----------------------------------------------------------------------------+"
	@echo "                            WELCOME TO OUR CUB3D :)       "
	@echo "Compilation flags: $(CFLAGS)"

%.o: %.c $(HDRS)
	@COUNT=$$(cat $(COUNTER_FILE) 2>/dev/null || echo 0); \
	COUNT=$$((COUNT + 1)); \
	echo $$COUNT > $(COUNTER_FILE); \
	STATE=$$(cat $(SPINNER_FILE) 2>/dev/null || echo 0); \
	CHARS='|/-\'; \
	CHAR=$$(printf '%s' "$$CHARS" | cut -c$$((STATE + 1))); \
	printf "\r\033[K\033[1;36m[%2d/%2d]\033[0m Compiling %-35s [\033[1;33m%s\033[0m]" "$$COUNT" "$(TOTAL_FILES)" "$(<F)" "$$CHAR"; \
	$(CC) $(CFLAGS) $(INC) -c $< -o $@; \
	echo $$(((STATE + 1) % 4)) > $(SPINNER_FILE)

clean:
	@rm -f $(OBJS) $(SPINNER_FILE) $(COUNTER_FILE)
	@if [ -d $(MLX_PATH) ] && [ -f $(MLX_PATH)/Makefile.gen ]; then \
		make -C $(MLX_PATH) clean 2>/dev/null || true; \
	fi
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@printf "\033[38;5;117m[ 1/ 1] ✓ All cleaned now!\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_PATH)
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@printf "\033[94m[ 1/ 1] ✓ And all fcleaned now as well! :D\033[0m\n"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
