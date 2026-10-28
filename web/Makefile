# Build cub3D against the SDL2 MiniLibX shim.
# Run from the repo root:  make -C web native
#                          make -C web wasm   (needs emcc on PATH)
#                          make -C web serve  (after wasm)

.DEFAULT_GOAL := native
.PHONY: native wasm serve clean fclean re

CC = cc
TARGET = cub3D_sdl
OBJ_DIR = obj/native
WASM_OBJ_DIR = obj/wasm
WASM_OUT = dist/index.html

GAME_SRCS = $(foreach d,../src ../src/input ../src/render ../src/parsing,$(wildcard $(d)/*.c))
LIBFT_SRCS = $(wildcard ../libft/*.c)

OBJS = $(patsubst ../%.c,$(OBJ_DIR)/%.o,$(GAME_SRCS) $(LIBFT_SRCS)) \
	$(OBJ_DIR)/mlx_sdl/mlx_sdl.o

WASM_OBJS = $(patsubst ../%.c,$(WASM_OBJ_DIR)/%.o,$(GAME_SRCS) $(LIBFT_SRCS)) \
	$(WASM_OBJ_DIR)/mlx_sdl/mlx_sdl.o

ASSETS = $(wildcard ../maps/*.cub) $(wildcard ../textures/XPMs/*.xpm)

# mlx_sdl comes first so that "mlx.h" resolves to the shim
INC = -I mlx_sdl -I ../include -I ../libft

CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -std=c99 -g \
	$(shell pkg-config --cflags sdl2)
DEPFLAGS = -MMD -MP
LDLIBS = $(shell pkg-config --libs sdl2) -lm

EMCC = emcc
EMCC_CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type -std=c99 -O2 -sUSE_SDL=2
EMCC_LDFLAGS = -O2 -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 \
	--preload-file ../maps@/maps \
	--preload-file ../textures/XPMs@/textures/XPMs \
	--shell-file shell.html -lm

native: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

$(OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

wasm: $(WASM_OUT)

$(WASM_OUT): $(WASM_OBJS) shell.html $(ASSETS)
	@mkdir -p dist
	$(EMCC) $(WASM_OBJS) -o $@ $(EMCC_LDFLAGS)

$(WASM_OBJ_DIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	$(EMCC) $(EMCC_CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

$(WASM_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(EMCC) $(EMCC_CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

serve:
	cd dist && python3 -m http.server 8000

-include $(OBJS:.o=.d) $(WASM_OBJS:.o=.d)

clean:
	rm -rf obj

fclean: clean
	rm -f $(TARGET)
	rm -rf dist

re: fclean native
