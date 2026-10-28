# Build cub3D against the SDL2 MiniLibX shim.
# Run from the repo root:  make -C web native

.DEFAULT_GOAL := native
.PHONY: native clean fclean re

CC = cc
TARGET = cub3D_sdl
OBJ_DIR = obj/native

GAME_SRCS = $(foreach d,../src ../src/input ../src/render ../src/parsing,$(wildcard $(d)/*.c))
LIBFT_SRCS = $(wildcard ../libft/*.c)

OBJS = $(patsubst ../%.c,$(OBJ_DIR)/%.o,$(GAME_SRCS) $(LIBFT_SRCS)) \
	$(OBJ_DIR)/mlx_sdl/mlx_sdl.o

# mlx_sdl comes first so that "mlx.h" resolves to the shim
INC = -I mlx_sdl -I ../include -I ../libft

CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -g \
	$(shell pkg-config --cflags sdl2)
DEPFLAGS = -MMD -MP
LDLIBS = $(shell pkg-config --libs sdl2) -lm

native: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -rf obj

fclean: clean
	rm -f $(TARGET)

re: fclean native
