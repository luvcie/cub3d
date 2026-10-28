# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pramos-c <pramos-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 15:03:18 by pramos-c          #+#    #+#              #
#    Updated: 2026/02/03 14:34:40 by lucpardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
WFLAGS = -Wall -Wextra -Werror -std=c2y
CFLAGS = $(WFLAGS) $(shell pkg-config --cflags sdl2)

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
       $(SRC_DIR)/parsing/parse_color.c \
       $(SRC_DIR)/parsing/validate_map.c \
       $(SRC_DIR)/parsing/validate_textures.c \
       $(SRC_DIR)/parsing/validate_walls.c \
       $(SRC_DIR)/parsing/free_game.c \
       $(SRC_DIR)/parsing/utils.c \
       mlx_sdl/mlx_sdl.c

OBJS = $(SRCS:.c=.o)
HDRS = $(INC_DIR)/cub3d.h mlx_sdl/mlx.h

# progress counter
TOTAL_FILES := $(words $(SRCS))
COUNTER_FILE := .compile_counter

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I$(LIBFT_PATH)

INC = -Imlx_sdl $(LIBFT_INC) -I$(INC_DIR)

all: $(NAME)

$(LIBFT):
	@printf "\033[1;36m[ Compiling libft ]\033[0m\n"
	@make -C $(LIBFT_PATH) --no-print-directory

$(NAME): $(LIBFT) $(OBJS)
	@rm -f $(COUNTER_FILE)
	@printf "\033[1;36m[ Linking $(NAME) ]\033[0m\n"
	$(CC) $(OBJS) -L$(LIBFT_PATH) -lft $(shell pkg-config --libs sdl2) -lm -o $(NAME)
	@printf "\033[1;32m✓ Build complete\033[0m\n"
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
	@echo "Compilation flags: $(WFLAGS)"

%.o: %.c $(HDRS)
	@COUNT=$$(cat $(COUNTER_FILE) 2>/dev/null || echo 0); \
	COUNT=$$((COUNT + 1)); \
	echo $$COUNT > $(COUNTER_FILE); \
	printf "\033[1;36m[%2d/%2d]\033[0m Compiling %s\n" "$$COUNT" "$(TOTAL_FILES)" "$<"
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(COUNTER_FILE)
	make -C $(LIBFT_PATH) clean
	@printf "\033[38;5;117m✓ All cleaned now!\033[0m\n"

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
	@printf "\033[94m✓ And all fcleaned now as well! :D\033[0m\n"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
